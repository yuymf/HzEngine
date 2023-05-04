#pragma once
#include <glm/glm.hpp>
#include "Hazel/RayTracing/Material.h"

namespace Hazel {

	class Sphere
	{
	public:
		Sphere(const glm::vec3& position, float radius, uint32_t entityID);

		void SetPosition(const glm::vec3& position);
		void SetRadius(const float radius);
		void SetMaterial(const Ref<Material>& material);
		void SetEntityID(uint32_t entityID);

		glm::vec3& GetPosition() { return m_Position; }
		float& GetRadius() { return m_Radius; }
		Ref<Material>& GetMaterial() { return m_Material; }
		uint32_t GetEntityID() { return m_EntityID; }

	private:
		glm::vec3 m_Position;
		float m_Radius;
		Ref<Material> m_Material;
		uint32_t m_EntityID;
	};

	using SphereMap = std::unordered_map<uint32_t, Ref<Sphere>>;
}
