#pragma once
#include "Hazel/Scene/Primitive/Sphere.h"
#include "RayTracingCamera.h"
#include "Hazel/Core/TimeStep.h"

namespace Hazel {

	class RayTracingScene
	{
	public:
		void OnUpdate(const Timestep& timeStep, const Ref<RayTracingCamera>& camera);
		void OnViewPortResize(uint32_t width, uint32_t height);
		void AddSphere(const Ref<Sphere>& sphere);
		SphereMap& GetSpheres();
		uint32_t GetRenderImage() const;

	private:
		SphereMap m_Spheres;
	};
}
