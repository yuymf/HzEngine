#pragma once

#include "Hazel/Scene/Scene.h"
#include <entt.hpp>

namespace Hazel {

	class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity entity, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args... args)
		{
			HZ_CORE_ASSERT(!HasComponent<T>(),"Entity already has component!");
			return m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!")
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent()
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			HZ_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!")
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		// use entt::null not 0;
		operator bool() const { return m_EntityHandle != entt::null; }

	private:
		// 需要default构造函数，因此要初始化
		entt::entity m_EntityHandle{ 0 };
		Scene* m_Scene = nullptr;
	};

}
