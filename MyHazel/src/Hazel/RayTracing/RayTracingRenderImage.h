#pragma once

#include "Hazel/RayTracing/Ray.h"
#include "Hazel/Renderer/Image/Image.h"
#include "Hazel/RayTracing/RayTracingCamera.h"
#include "Hazel/RayTracing/RayTracingScene.h"

class Sphere;
class Material;

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
		static void OnRender(const SphereMap& spheres);
		static void EndScene();
		static uint32_t GetImage();

	private:
		static glm::vec4 PerPixel(Ref<Ray> ray, const SphereMap& spheres);
		static Ref<HitInfo> CastRay(const Ref<Ray>& castRay, const SphereMap& spheres);
		  
	private:
		static Ref<Image> m_Image;
		static Ref<RayTracingData> m_RayTracingData;
	};
}
