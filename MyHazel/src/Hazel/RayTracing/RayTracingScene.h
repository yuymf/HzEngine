#pragma once
#include "Hazel/Scene/Primitive/SpherePrimitive.h"
#include "RayTracingCamera.h"
#include "Hazel/Core/TimeStep.h"

namespace Hazel {

	class RayTracingScene
	{
	public:
		void OnUpdate(const Timestep& timeStep, const Ref<RayTracingCamera>& camera);
		void OnViewPortResize(uint32_t width, uint32_t height);
		uint32_t GetRenderImage()const;
	private:

		std::vector<SpherePrimitive> m_SpherePrimitve;
	};
}
