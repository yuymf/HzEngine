#include "hzpch.h"
#include "RayTracingRenderImage.h"
#include "Hazel/RayTracing/Ray.h"
#include "Hazel/Renderer/Image/Image.h"

namespace Hazel {

	Ref<Image> RayTracingRenderImage::m_Image = nullptr;
	Ref<RayTracingRenderImage::RayTracingData> RayTracingRenderImage::m_RayTracingData = nullptr;

	void RayTracingRenderImage::Init()
	{
		m_Image = CreateRef<Image>();
		m_RayTracingData = CreateRef<RayTracingData>();
		m_RayTracingData->rayData = CreateRef<Ray>();
		m_RayTracingData->viewMat = glm::mat4(1.0f);
		m_RayTracingData->projectionMat = glm::mat4(1.0f);
	}

	void RayTracingRenderImage::OnWindowResize(uint32_t width, uint32_t height)
	{
		if (width!= m_Image->GetWidth() || height != m_Image->GetHeight())
		{
			m_Image->Resize(width, height);
		}
	}

	void RayTracingRenderImage::BeginScene(const Ref<RayTracingCamera>& camera)
	{
		m_RayTracingData->rayData->Origin = camera->GetPosition();
		m_RayTracingData->viewMat = camera->GetInverseView();
		m_RayTracingData->projectionMat = camera->GetInverseProjection();
	}

	void RayTracingRenderImage::OnRender(const SphereMap& spheres)
	{
		if (spheres.empty()) 
		{
			return;
		}

		auto width = m_Image->GetWidth();
		auto height = m_Image->GetHeight();

		auto imageData = m_Image->GetImageData();
		for (uint32_t y = 0; y < height; y++)
		{
			for (uint32_t x = 0; x < width; x++)
			{
				glm::vec2 vec2Coord = { static_cast<float>(x) / static_cast<float>(width),
					static_cast<float>(y) / static_cast<float>(height) };
				vec2Coord = vec2Coord * 2.f - 1.f; 

				glm::vec4 target = m_RayTracingData->projectionMat * glm::vec4(vec2Coord.x, vec2Coord.y, 1, 1);
				m_RayTracingData->rayData->Direction = glm::vec3(m_RayTracingData->viewMat * 
					glm::vec4(glm::normalize(glm::vec3(target) / target.w), 0)); // World space

				imageData[x + y * width] = Image::ConvertToRGBA(PerPixel(m_RayTracingData->rayData, spheres));
			}
		}
	}

	void RayTracingRenderImage::EndScene()
	{
		m_Image->UpdateImage();
	}

	uint32_t RayTracingRenderImage::GetImage()
	{
		return m_Image->GetImage();
	}

	glm::vec4 RayTracingRenderImage::PerPixel(Ref<Ray> ray, const SphereMap& spheres)
	{
		glm::vec3 outColor(glm::vec3(0.0f, 0.0f, 0.0f));
		uint8_t rayBounces = 2;
		float multiplier = 1.0f;

		// Light Initial
		auto calcRay = CreateRef<Ray>();
		calcRay->Origin = ray->Origin;
		calcRay->Direction = ray->Direction;

		// Bounce Loop
		for (int i = 0; i < rayBounces; i++)
		{
			auto hitPayload = CastRay(calcRay, spheres);
			if (hitPayload == nullptr)
			{
				break;
			}
			// Out part:
			const auto& sphere = spheres.find(hitPayload->EntityID)->second;
			glm::vec3 baseColor = sphere->GetMaterial()->GetAlbedo();

			glm::vec3 lightDir = glm::normalize(glm::vec3(-1.f, -1.f, -1.f));
			glm::vec3 normal = hitPayload->WorldNormal;

			// Light:
			float diffuse = glm::max(glm::dot(normal, -lightDir), 0.f);

			outColor += multiplier * diffuse * baseColor;

			// Attenuation:
			multiplier *= 0.7f;
			calcRay->Origin = hitPayload->WorldPosition + hitPayload->WorldNormal * 0.0001f;
			calcRay->Direction = glm::reflect(calcRay->Direction, hitPayload->WorldNormal);
		}
		return glm::vec4(outColor, 1);
	}

	// View this func just ShaderToy's input
	Ref<HitInfo> RayTracingRenderImage::CastRay(const Ref<Ray>& castRay, const SphereMap& spheres)
	{
		// 1.Ray hit which Sphere:
		Ref<Sphere> hitSphere = nullptr;
		float hitDistance = std::numeric_limits<float>::max();
		for (const auto& it : spheres)
		{
			const auto& sphere = it.second;
			float radius = sphere->GetRadius();
			glm::vec3 origin = castRay->Origin - sphere->GetPosition();

			// Cal part:
			float fA = glm::dot(castRay->Direction, castRay->Direction);
			float fB = 2.f * glm::dot(origin, castRay->Direction);
			float fC = glm::dot(origin, origin) - radius * radius;
			float discriminant = fB * fB - 4.0f * fA * fC;

			if (discriminant < 0.0f) continue;  // if miss, next sphere

			float clostHit = (-fB - glm::sqrt(discriminant)) / (2.f * fA);
			//float h1 = (-fB + glm::sqrt(discriminant)) / (2.f * fA);

			if (clostHit > 0.f && clostHit < hitDistance)
			{
				hitDistance = clostHit;
				hitSphere = sphere;
			}
		}

		if (hitSphere == nullptr)
			return nullptr;

		// 2. Treat the hit Sphere, Note the hitInfo:
		auto hitInfo = CreateRef<HitInfo>();
		hitInfo->HitDistance = hitDistance;
		hitInfo->WorldPosition = castRay->Origin + castRay->Direction * hitDistance;
		hitInfo->WorldNormal = glm::normalize(hitInfo->WorldPosition - hitSphere->GetPosition());
		hitInfo->EntityID = hitSphere->GetEntityID();

		return hitInfo;
	}

}
