#include "hzpch.h"
#include "Hazel/RayTracing/Material.h"

namespace Hazel {

	Material::Material()
		: m_Albedo(glm::vec3(0.0f)), m_Roughness(1.0f), m_Metallic(0.0f)
	{

	}


	void Material::SetAlbedo(const glm::vec3& albedo)
	{
		m_Albedo = albedo;
	}


	void Material::SetRoughness(float roughness)
	{
		m_Roughness = roughness;
	}


	void Material::SetMetallic(float metallic)
	{
		m_Metallic = metallic;
	}

}
