#include "hzpch.h"
#include "RayTracingScene.h"
#include "RayTracingRenderImage.h"

namespace Hazel {

	void RayTracingScene::OnUpdate(const Timestep& timeStep, const Ref<RayTracingCamera>& camera)
	{
		RayTracingRenderImage::BeginScene(camera);
	}

	void RayTracingScene::OnViewPortResize(uint32_t width, uint32_t height)
	{
		RayTracingRenderImage::OnWindowResize(width, height);
	}

	uint32_t RayTracingScene::GetRenderImage() const
	{
		return RayTracingRenderImage::GetImage();
	}
}
