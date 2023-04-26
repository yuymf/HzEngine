#include "hzpch.h"
#include "RayTracingRenderImage.h"
#include "Hazel/RayTracing/Ray.h"
#include "Hazel/Renderer/Image/Image.h"

namespace Hazel {

	Ref<Image> RayTracingRenderImage::m_Image = nullptr;

	void RayTracingRenderImage::Init()
	{
		m_Image = CreateRef<Image>();
	}

	void RayTracingRenderImage::OnWindowResize(uint32_t width, uint32_t height)
	{
		if (width!= m_Image->GetWidth() || height != m_Image->GetHeight())
		{
			m_Image->Resize(width, height);
		}
	}

	void RayTracingRenderImage::BeginScene(const Ref<RayTracingCamera>& camera)
	{
		auto width = m_Image->GetWidth();
		auto height = m_Image->GetHeight();
		// Cast ray from camera:
		auto ray = CreateRef<Ray>();
		ray->Origin = camera->GetPosition();
		const auto& view = camera->GetInverseView();
		const auto& projection = camera->GetInverseProjection();

		auto imageData = m_Image->GetImageData();
		for (uint32_t y = 0; y < height; y++)
		{
			for (uint32_t x = 0; x < width; x++)
			{
				glm::vec2 vec2Coord = { static_cast<float>(x) / static_cast<float>(width),
					static_cast<float>(y) / static_cast<float>(height) };
				vec2Coord = vec2Coord * 2.f - 1.f; //(0~1)->(-1,1)
				// Get every direction:
				glm::vec4 target = projection * glm::vec4(vec2Coord.x, vec2Coord.y, 1, 1);
				ray->Direction = glm::vec3(view * glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space

				imageData[x + y * width] = Image::ConvertToRGBA(CastRay(ray));
			}
		}
		m_Image->UpdateImage();
	}

	void RayTracingRenderImage::EndScene()
	{

	}

	uint32_t RayTracingRenderImage::GetImage()
	{
		return m_Image->GetImage();
	}

	// View this func just ShaderToy's input
	glm::vec4 RayTracingRenderImage::CastRay(const Ref<Ray>& ray)
	{
		// Sub part:
		float radius(0.5f);
		glm::vec3 baseColor = glm::vec3(1, 0, 1);

		// Cal part:
		float fA = glm::dot(ray->Direction, ray->Direction);
		float fB = 2.f * glm::dot(ray->Origin, ray->Direction);
		float fC = glm::dot(ray->Origin, ray->Origin) - radius * radius;
		float discriminant = fB * fB - 4.0f * fA * fC;

		if (discriminant < 0.0f)
			return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		float h0 = (-fB - glm::sqrt(discriminant)) / (2.f * fA);
		float h1 = (-fB + glm::sqrt(discriminant)) / (2.f * fA);

		glm::vec3 clostHitPoint = ray->Origin + ray->Direction * h0;
		// Out part:
		glm::vec3 lightDir = glm::normalize(glm::vec3(-1.f, -1.f, -1.f));
		glm::vec3 normal = glm::normalize(clostHitPoint);

		// Light:
		float diffuse = glm::max(glm::dot(normal, -lightDir), 0.f);
		glm::vec3 color = diffuse * baseColor;

		return glm::vec4(color, 1);
	}

}
