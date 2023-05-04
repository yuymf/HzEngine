#pragma once
#include <glm/glm.hpp>

namespace Hazel {

	class Material
	{
	public:
		Material();

		void SetAlbedo(const glm::vec3& albedo);
		void SetRoughness(float roughness);
		void SetMetallic(float metallic);

		glm::vec3& GetAlbedo() { return m_Albedo; }
		float GetRoughness() { return m_Roughness; }
		float GetMetallic() { return m_Metallic; }

	private:
		glm::vec3 m_Albedo;
		float m_Roughness;
		float m_Metallic;

	};
}
