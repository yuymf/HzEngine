#include "hzpch.h"
#include "RendererImage.h"

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
				imageData[x + y * width] = GetPerPixel(vec2Coord);
			}
		}
		m_Image->UpdateImage();
	}


	uint32_t RendererImage::GetImage()
	{
		return m_Image->GetImage();
	}

	uint32_t RendererImage::GetPerPixel(const glm::vec2& vecCoord)
	{
		uint8_t r = static_cast<uint8_t>(vecCoord.x * UCHAR_MAX);
		uint8_t g = static_cast<uint8_t>(vecCoord.y * UCHAR_MAX);
		return 0xff000000 | (g << 8) | r;
	}

}
