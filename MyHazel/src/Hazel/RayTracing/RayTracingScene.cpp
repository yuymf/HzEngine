#include "hzpch.h"
#include "RayTracingScene.h"
#include "RayTracingRenderImage.h"

namespace Hazel {

	void RayTracingScene::OnUpdate(const Timestep& timeStep, const Ref<RayTracingCamera>& camera)
	{
		RayTracingRenderImage::BeginScene(camera);
		RayTracingRenderImage::OnRender(m_Spheres);
		RayTracingRenderImage::EndScene();

	}

	void RayTracingScene::OnViewPortResize(uint32_t width, uint32_t height)
	{
		RayTracingRenderImage::OnWindowResize(width, height);
	}

	void RayTracingScene::AddSphere(const Ref<Sphere>& sphere)
	{
		m_Spheres.push_back(sphere);
	}

	std::vector<Ref<Sphere>> RayTracingScene::GetSpheres() const
	{
		return m_Spheres;
	}

	uint32_t RayTracingScene::GetRenderImage() const
	{
		return RayTracingRenderImage::GetImage();
	}
}
