#include "hzpch.h"
#include "RendererImage.h"
#include "Hazel/Renderer/Image/Image.h"

namespace Hazel {

	Ref<Image> RendererImage::m_Image = nullptr;

	void RendererImage::Init()
	{
		m_Image = CreateRef<Image>();
	}

	void RendererImage::OnWindowResize(uint32_t width, uint32_t height)
	{
		if (width!= m_Image->GetWidth() || height != m_Image->GetHeight())
		{
			m_Image->Resize(width, height);
		}
	}

	void RendererImage::OnRender()
	{
		auto width = m_Image->GetWidth();
		auto height = m_Image->GetHeight();

		auto imageData = m_Image->GetImageData();
		for (uint32_t y = 0; y < height; y++)
		{
			for (uint32_t x = 0; x < width; x++)
			{
				glm::vec2 vec2Coord = { static_cast<float>(x) / static_cast<float>(width),
					static_cast<float>(y) / static_cast<float>(height) };
				// Note this!
				vec2Coord = vec2Coord * 2.f - 1.f; //(0~1)->(-1,1)
				imageData[x + y * width] = Image::ConvertToRGBA(CastRay(vec2Coord));
			}
		}
		m_Image->UpdateImage();
	}

	uint32_t RendererImage::GetImage()
	{
		return m_Image->GetImage();
	}

	// View this func just ShaderToy's input
	glm::vec4 RendererImage::CastRay(const glm::vec2& fragCoord)
	{
		// Sub part:
		glm::vec3 rayOrigin(0.0f, 0.0f, 1.0f);
		glm::vec3 rayDirection(fragCoord.x, fragCoord.y, -1.0f);
		float radius(0.5f);
		glm::vec3 lightDir = glm::normalize(glm::vec3(-1.f, -1.f, -1.f));
		glm::vec3 baseColor = glm::vec3(1, 0, 1);

		// Cal part:
		float fA = glm::dot(rayDirection, rayDirection);
		float fB = 2.f * glm::dot(rayOrigin, rayDirection);
		float fC = glm::dot(rayOrigin, rayOrigin) - radius * radius;
		float discriminant = fB * fB - 4.0f * fA * fC;

		if (discriminant < 0.0f)
			return glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

		float h0 = (-fB - glm::sqrt(discriminant)) / (2.f * fA);
		float h1 = (-fB + glm::sqrt(discriminant)) / (2.f * fA);

		glm::vec3 clostHitPoint = rayOrigin + rayDirection * h0;
		glm::vec3 normal = glm::normalize(clostHitPoint);

		// Out part:
		float diffuse = glm::max(glm::dot(normal, -lightDir), 0.f);
		//glm::vec3 color = normal * 0.5f + 0.5f;
		glm::vec3 color = diffuse * baseColor;

		return glm::vec4(color, 1);
	}

}
