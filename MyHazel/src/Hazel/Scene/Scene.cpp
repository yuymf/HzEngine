#include "hzpch.h"
#include "Hazel/Scene/Scene.h"

#include <glm/glm.hpp>

namespace Hazel {

	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{

	}


	struct TransformComponent
	{
		glm::mat4 Transform;

		TransformComponent() = default;
		TransformComponent(const TransformComponent&) = default;
		TransformComponent(const glm::mat4& transform)
			: Transform(transform) {}

		// operator: TransformComponent equals glm::mat4&; used in Has && Get;
		operator glm::mat4& () { return Transform; }
		operator const glm::mat4& () const { return Transform; }
	};

	struct SpiritRendererComponent
	{
		glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

		SpiritRendererComponent() = default;
		SpiritRendererComponent(const SpiritRendererComponent&) = default;
		SpiritRendererComponent(const glm::vec4 & color)
			: Color(color) {}
	};

	Scene::Scene()
	{
#if ENTT_EXAMPLE_CODE
		// Create
		entt::entity entity = m_Registry.create();							//entt::entity equals uint_32;
	
		// Emplace
		m_Registry.emplace<TransformComponent>(entity, glm::mat4(1.0f));
		
		// Construct
		m_Registry.on_construct<TransformComponent>().connect<&OnTransformConstruct>();

		// Has && Get
		if (m_Registry.has<TransformComponent>(entity))
		{
			TransformComponent& transform = m_Registry.get<TransformComponent>(entity);
		}

		// View
		auto view = m_Registry.view<TransformComponent>();
		for (auto& entity : view)
		{
			TransformComponent& transform = view.get<TransformComponent>(entity);
		}

		// Group
		auto group = m_Registry.group<TransformComponent>(entt::get<SpiritRendererComponent>);
		for (auto& entity : group)
		{
			auto& [transform, mesh] = group.get<TransformComponent, SpiritRendererComponent>(entity);
		}
#endif
	}

	Scene::~Scene()
	{

	}

}