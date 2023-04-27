#include "hzpch.h"
#include "Sphere.h"

namespace Hazel {

	Sphere::Sphere(const glm::vec3& position, float radius, Ref<RayTracingMaterial> rayTracingMaterial)
		: m_Position(position), m_Radius(radius), m_Material(rayTracingMaterial)
	{

	}
}

