#pragma once

#include "Hazel/RayTracing/Ray.h"
#include "Hazel/Renderer/Image/Image.h"
#include "Hazel/RayTracing/RayTracingCamera.h"
#include "Hazel/RayTracing/RayTracingScene.h"

class Sphere;
class RayTracingMaterial;

namespace Hazel {

	class RayTracingRenderImage
	{
	public:
		struct RayTracingData
		{
			Ref<Ray> rayData;
			glm::mat4 viewMat;
			glm::mat4 projectionMat;
		};

		static void Init();
		static void OnWindowResize(uint32_t width, uint32_t height);
		static void BeginScene(const Ref<RayTracingCamera>& camera);
		static void OnRender(const std::vector<Ref<Sphere>>& spheres);
		static void EndScene();
		static uint32_t GetImage();

	private:
		static glm::vec4 CastRay(const std::vector<Ref<Sphere>>& spheres);

	private:
		static Ref<Image> m_Image;
		static Ref<RayTracingData> m_RayTracingData;
	};
}
