#pragma once
#include <glm/glm.hpp>

namespace Hazel {

	class RayTracingMaterial
	{
	public:
		RayTracingMaterial(const glm::vec3& albedo);

		glm::vec3& GetAlbedo() { return m_Albedo; }
	private:
		glm::vec3 m_Albedo;

	};
}
