#include "hzpch.h"
#include "Image.h"
#include "Hazel/Math/Random.h"

namespace Hazel {

	Image::Image(InternalFormat internalFormat /*= InternalFormat::RGBA32F*/, DataFormat dataFormat /*= DataFormat::RGBA*/)
	{
		m_DataBuffer = CreateRef<DataBuffer>(0, dataFormat == DataFormat::RGBA ? 4 : 3);
		m_Texture = Texture2D::Create(0, 0, internalFormat, dataFormat);
	}

	Image::Image(uint32_t width, uint32_t height, InternalFormat internalFormat /*= InternalFormat::RGBA32F*/, DataFormat dataFormat /*= DataFormat::RGBA*/)
	{
		m_DataBuffer = CreateRef<DataBuffer>(width * height, dataFormat == DataFormat::RGBA ? 4 : 3);
		m_Texture = Texture2D::Create(width, height, internalFormat, dataFormat);
	}

	uint32_t* Image::GetImageData()
	{
		return m_DataBuffer->As<uint32_t>();
	}

	void Image::Resize(uint32_t width, uint32_t height)
	{
		m_DataBuffer->Resize(width * height);
		m_Texture->Resize(width, height);
	}

	uint32_t Image::GetWidth() const
	{
		return m_Texture->GetWidth();
	}


	uint32_t Image::GetHeight() const
	{
		return m_Texture->GetHeight();
	}


	uint32_t Image::GetImage() const
	{
		//m_Texture->SetData(m_DataBuffer->As<uint32_t>(), m_DataBuffer->GetDataBufferSize());
		// Bug Fixed: When GetImage Don't UpdateData(setData) !
		return m_Texture->GetRendererID();
	}

	void Image::UpdateImage()
	{
		m_Texture->SetData(m_DataBuffer->As<uint32_t>(), m_DataBuffer->GetDataBufferSize());
	}

	uint32_t Image::ConvertToRGBA(const glm::vec4& color)
	{
		auto clampColor = glm::clamp(color, glm::vec4(0.f), glm::vec4(1.f));
		uint8_t r = static_cast<uint8_t>(clampColor.r * 255.0f);
		uint8_t g = static_cast<uint8_t>(clampColor.g * 255.0f);
		uint8_t b = static_cast<uint8_t>(clampColor.b * 255.0f);
		uint8_t a = static_cast<uint8_t>(clampColor.a * 255.0f);
		uint32_t result = a << 24 | b << 16 | g << 8 | r;
		return result;
	}

}
