# HzEngine
A C++ Mini Game Engine!

This project is based on the Hazel engine of the Cherno. Thank you very much for Cherno's open source and videos.

![20230311100306](img/20230311100306.png)

This project includes spdlog log system, glfw event system, Layer layer design, Imgui input interface and visual debugging，OpenGLRendering

1. LogSystem：Create the Log class, and then have s_ CoreLogger and s_ ClientLogger, which processes engine logs and client logs respectively.

2. EventSystem：Event&EventDispatcher: Mouse Event、Window Event、ApplicationEvent and KeyEvent.

3. LayerStack: A vector is used to simulate a stack as a container, and vector [0] is used as the top of the stack. The layer at the top of the stack is the closest layer to us on the screen. This layer receives the event first, and is finally rendered.

4. InputSystem: The input instance can use the singleton mode. The interface exposed by the singleton is the static function, and the specific implementation method is the virtual function of the singleton.

5. ImguiDocking: Docking of Imgui to realize editor dragging.

6. OpenGLRendering: VBO、VAO、EBO、shader    

   Abstraction：

   Vertex Buffer Layouts：

   ```cpp
   BufferLayout layout = { 
   	{ ShaderDataType::Float3, "a_Position"}, 
   	{ ShaderDataType::Float2, "a_TexCoord"} };
   m_VertexBuffer->SetBufferLayout(layout);
   ```

   Vertex Arrays：

   ```cpp
   void OpenGLVertexArray::AddVertexBuffer(std::shared_ptr<VertexBuffer>& vertexBuffer)
   {
   	HAZEL_CORE_ASSERT(vertexBuffer->GetBufferLayout().GetCount(), "Empty Layout in VertexBuffer!");
   	BufferLayout layout = vertexBuffer->GetBufferLayout();
   	int index = 0;
   	for (const BufferElement& element : layout)
   	{
   		glEnableVertexAttribArray(index);
   		glVertexAttribPointer(index,
   			GetShaderTypeDataCount(element.GetType()),
   			GetShaderDataTypeToOpenGL(element.GetType()),
   			element.IsNormalized() ? GL_TRUE : GL_FALSE,
   			layout.GetStride(),
   			(const void*)(element.GetOffset()));
   		index++;
   	}
   }
   ```

   shaer、EBO part is easy


7. Camera： P * V：OrthographicCamera&EditorCamera

8. Timestep system：By multiplying the motion in each frame by the time elapsed in that frame, you can counteract the problem of data inconsistencies caused by frame rate.

9. Profiling: Instumentor.h

10. Batching Rendering: Modify the DrawQuad function to dynamically populate Vertex Buffer with vertex attribute data to be drawn when drawing.

    VertexBuffer: GL_STATIC_DRAW to GL_DYNAMIC_DRAW

```cpp
void glBufferSubData(GLenum target, GLintptr offset, GLsizeiptr size, const void * data);
void glNamedBufferSubData(GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data)
```

Batching Rendering Textures: In order for the DrawQuad function to use the same texture together, the same texture can be used.

```cpp
glBindTextureUnit(slot, m_RendererID);
```

11. Editor

12. FrameBuffer : Resize:change the camera frustum

13. ECS: entt(Add、Has、Get)
14. UI
15. File system: Saving and Loading Scenes: YAML 、Open/Save File Dialogs：：https://docs.microsoft.com/en-us/office/[vba](https://so.csdn.net/so/search?q=vba&spm=1001.2101.3001.7020)/api/excel.application.getopenfilename

16. Gizmos：ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection), ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(transform));

17. Multiple Render Targets and Framebuffer Refactor：Click on the corresponding GameObject in the Viewport

18. SPIR-V & shaderc:

    A)SPIR-V's compiler compiles Vulkan's shader into an intermediate language:

    *1. 创建编译器: shaderc提供的glslang编译器*

    *2. 遍历并编译每个shader, 比如vert或frag, 为其生成一个单独的binary文件*,*如果有现成的缓存文件, 那么直接读取该文件, 存到data里*,*否则编译出新的文件,把glsl文件编译为Spir-v* 

    ```cpp
    *shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source,Utils::GLShaderStageToShaderC(stage), m_FilePath.c_str(), options);*
    ```

    *3. 所有的shader都读到shaderData*

    B)SPIR-V's cross-platform compiler, such as GLSL, is translated for use on OpenGL

    1.*获取shader缓存目录*

    2.*编译为string，写为shaderdata*

    ```
    *shaderc::SpvCompilationResult module = compiler.CompileGlslToSpv(source, Utils::GLShaderStageToShaderC(stage), m_FilePath.c_str());*
    ```

19. UniformBuffer：A piece of memory located on the GPU can be shared by all Shader

```
// 0 uniform buffer
layout(std140, binding = 0) uniform Transform
{
	mat4 Transform;
}
```

```cpp
std::vector<GLuint> shaderIDs;
for (auto&& [stage, spirv] : m_OpenGLSPIRVCache)
{
	GLuint shaderID = shaderIDs.emplace_back(glCreateShader(Utils::ShaderTypeToOpenGL(stage)));
	glShaderBinary(1, &shaderID, GL_SHADER_BINARY_FORMAT_SPIR_V, spirv.data(), spirv.size() * sizeof(uint32_t));
	glSpecializeShader(shaderID, "main", 0, nullptr, nullptr);
	glAttachShader(m_RendererID, shaderID);
}
```

