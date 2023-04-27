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
		std::vector<Ref<Sphere>> GetSpheres() const;
		uint32_t GetRenderImage() const;
	private:

		std::vector<Ref<Sphere>> m_Spheres;
	};
}
