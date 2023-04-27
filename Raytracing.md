## RayTracing

### 1. Image Render

##### Q1. GL_Texture format error

单步调试，发现问题出在Image::GetImage()， When GetImage Don't UpdateData(setData)，这样会导致databuffer尺寸不匹配

##### Q2. 图片上下翻转

```cpp
ImGui::Image((void*)image, m_RenderViewPortSize, ImVec2(0, 1), ImVec2(1, 0));
```

ImGUI默认从（0，0）到（1， 1），从左上到右下（左手）.

##### Q3.材质提交和设置材质数据

glTextureStorage2D，glTexImage2D：使用下面可以提交DataFormat

```cpp
//glTextureStorage2D(m_RendererID, 1, m_InternalFormat, m_Width, m_Height);
glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0,
m_DataFormat, GL_UNSIGNED_BYTE, nullptr);
```

glTextureSubImage2D：提交Data（Void* 内存）

```cpp
glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
```

### 2. Render Sphere：

光线从相机位置出发，穿过UV， 与圆求交（解二元一次方程）

##### Base:

<img src="img/image-20230426164746584.png" alt="image-20230426164746584" style="zoom:50%;" />

##### Shadow: 

<img src="img/image-20230426164639516.png" alt="image-20230426164639516" style="zoom:50%;" />

##### Q1.  球渲染不全

将UV坐标转换，in RenderImage‘s Forloop

```cpp
vec2Coord = vec2Coord * 2.f - 1.f; //(0~1)->(-1,1)
```

<img src="img/image-20230426112107993.png" alt="image-20230426112107993" style="zoom:50%;" />

##### Q2 性能优化：只是为了求Fa不要对rayDirection归一化

额外性能付出，需要求模

```cpp
// rayDirection = normalize(rayDirection);
// float fA = 1.0f;
float fA = glm::dot(rayDirection, rayDirection);
```

##### Q3 0xff00000 -> vec4(0, 0, 0, 1)

![image-20230426153507163](img/image-20230426153507163.png)

a << 24 | b << 16 | g << 8 | r

### 3.Camera

##### Q1. GL Error

![image-20230427093040518](img/image-20230427093040518.png)

同样问题发生在image ::setdata上，m_RenderViewPortSize（渲染窗口）初始化为0，会给一个0大小的texture data，从而报错，在场景resize之前加上

```cpp
if (m_RenderViewPortSize.x > 0 && m_RenderViewPortSize.y > 0)
```

##### Q2.  性能优化：Raytracing camera

给定一个flag如moved，当Input::IsKeyPressed（）后，flag为true，重新计算V矩阵！

将光线方向缓存，只有动的时候重新计算几个大矩阵！

##### Q3. Projection计算

![image-20230427101543809](img/image-20230427101543809.png)

```cpp
m_Projection = glm::perspectiveFov(glm::radians(m_VerticalFOV), (float)m_ViewportWidth, (float)m_ViewportHeight, m_NearClip, m_FarClip);
```

##### Q4. View矩阵计算

```
m_View = glm::lookAt(m_Position, m_Position + m_ForwardDirection, glm::vec3(0, 1, 0));
```

（RUT摆列）注意，glm::lookat分左手（Opengl）和右手（其他），注意第三列（z旋转）和32符号（z平移）不同（因为z轴指向不同）！！

Opengl：左手

![image-20230427094616314](img/image-20230427094616314.png)

右手：

![image-20230427094655420](img/image-20230427094655420.png)

##### Q5. 相机的旋转使用四元数

通过四元数q，旋转前向方向

```cpp
glm::quat q = glm::normalize(glm::cross(glm::angleAxis(-pitchDelta, rightDirection),
				glm::angleAxis(-yawDelta, glm::vec3(0.f, 1.0f, 0.0f))));
m_ForwardDirection = glm::rotate(q, m_ForwardDirection);
```

##### Q6. 屏幕空间->观察空间->世界空间

重新计算光线方向：由于左手（PVM*World = View）-> (World = M-1 * V-1 * P-1 * View)

```cpp
coord = coord * 2.0f - 1.0f; // -1 -> 1
glm::vec4 target = m_InverseProjection * glm::vec4(coord.x, coord.y, 1, 1);
glm::vec3 rayDirection = glm::vec3(m_InverseView  *glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space
```

**glm::vec3(target) / target.w)** : 将 `target` 的前三个分量除以其 w 分量，可以将其还原为一个方向向量

