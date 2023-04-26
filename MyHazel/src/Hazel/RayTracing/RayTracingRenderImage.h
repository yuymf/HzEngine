#pragma once

#include "Hazel/RayTracing/Ray.h"
#include "Hazel/Renderer/Image/Image.h"
#include "Hazel/RayTracing/RayTracingCamera.h"

namespace Hazel {

	class RayTracingRenderImage
	{
	public:
		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(const Ref<RayTracingCamera>& camera);
		static void EndScene();
		static uint32_t GetImage();

	private:
		static glm::vec4 CastRay(const Ref<Ray>& ray);

	private:
		static Ref<Image> m_Image;
	};
}
