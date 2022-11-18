#include "hzpch.h"
#include "Hazel/Scene/Scene.h"
#include "Hazel/Scene/Entity.h"
#include "Components.h"
#include "Hazel/Renderer/Renderer2D.h"

#include <glm/glm.hpp>

namespace Hazel {

	static void DoMath(const glm::mat4& transform)
	{

	}

	static void OnTransformConstruct(entt::registry& registry, entt::entity entity)
	{

	}

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

	Entity Scene::CreateEntity(const std::string& name)
	{
		Entity entity = { m_Registry.create(), this };
		entity.AddComponent<TransformComponent>();
		auto& tag = entity.AddComponent<TagComponent>();
		tag.Tag = name.empty() ? "Entity" : name;
		return entity;
	}

	void Scene::OnUpdate(Timestep ts)
	{
		auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRendererComponent>);
		for (auto entity : group)
		{
			auto& [transform, sprite] = group.get<TransformComponent, SpriteRendererComponent>(entity);

			Renderer2D::DrawQuad(transform, sprite.Color);
		}
	}

}