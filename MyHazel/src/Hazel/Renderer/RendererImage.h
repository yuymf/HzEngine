#pragma once

#include "Hazel/Renderer/Renderer.h"
#include "Hazel/Renderer/Image/Image.h"

namespace Hazel {

	class RendererImage
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void OnRender();
		static uint32_t GetImage();
	private:
		static glm::vec4 CastRay(const glm::vec2& fragCoord);
		static Ref<Image> m_Image;
	};
}
