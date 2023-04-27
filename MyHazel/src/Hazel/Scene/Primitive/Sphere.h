#pragma once
#include <glm/glm.hpp>
#include "Hazel/RayTracing/RayTracingMaterial.h"

namespace Hazel {

	class Sphere
	{
	public:
		Sphere(const glm::vec3& position, float radius, Ref<RayTracingMaterial> rayTracingMaterial);
		glm::vec3& GetPosition() { return m_Position; }
		float& GetRadius() { return m_Radius; }
		Ref<RayTracingMaterial>& GetMaterial() { return m_Material; }
	private:
		glm::vec3 m_Position;
		float m_Radius;
		Ref<RayTracingMaterial> m_Material;
	};
}
