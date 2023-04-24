#pragma once

#include "Hazel/Renderer/Texture.h"
#include "Hazel/Core/DataBuffer.h"

namespace Hazel {

	class Image
	{
	public:
		//Image(uint32_t width, uint32_t height, InternalFormat internalFormat, DataFormat dataFormat);
		Image(InternalFormat internalFormat = InternalFormat::RGBA32F, DataFormat dataFormat = DataFormat::RGBA);
		Image(uint32_t width, uint32_t height,
			InternalFormat internalFormat = InternalFormat::RGBA32F, DataFormat dataFormat = DataFormat::RGBA);
		uint32_t* GetImageData();
		uint32_t GetWidth() const;
		uint32_t GetHeight() const;
		uint32_t GetImage() const;

		void UpdateImage();
		void Resize(uint32_t width, uint32_t height);

	private:
		Ref<Texture2D> m_Texture;
		Ref<DataBuffer> m_DataBuffer;
	};
}
