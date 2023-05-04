#include "hzpch.h"
#include "Sphere.h"

namespace Hazel {

	Sphere::Sphere(const glm::vec3& position, float radius, uint32_t entityID)
		: m_Position(position), m_Radius(radius), m_Material(nullptr), m_EntityID(entityID)
	{

	}

	void Sphere::SetPosition(const glm::vec3& position)
	{
		m_Position = position;
	}

	void Sphere::SetRadius(const float radius)
	{
		m_Radius = radius;
	}

	void Sphere::SetMaterial(const Ref<Material>& material)
	{
		m_Material = material;
	}

	void Sphere::SetEntityID(uint32_t entityID)
	{
		m_EntityID = entityID;
	}

}

