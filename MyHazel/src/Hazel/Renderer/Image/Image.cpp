#include "hzpch.h"
#include "Image.h"

namespace Hazel {

	Image::Image(uint32_t width, uint32_t height, InternalFormat internalFormat, DataFormat dataFormat)
		: m_DataBuffer(CreateRef<DataBuffer>(width* height * 4))
	{
		m_Texture = Texture2D::Create(width, height, internalFormat, dataFormat);
	}

	uint32_t* Image::GetImageData()
	{
		return m_DataBuffer->As<uint32_t>();
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
		m_Texture->SetData(m_DataBuffer->As<uint32_t>(), m_DataBuffer->GetDataBufferSize());
		return m_Texture->GetRendererID();
	}

}
