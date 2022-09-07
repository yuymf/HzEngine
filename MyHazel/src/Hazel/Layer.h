#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hazel {

	class HAZEL_API Layer													//if miss HAZEL_API, link error appears at Sandbox.exe;
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdate() {}
		virtual void OnEvent(Event& event) {}

		const std::string& GetName() const { return m_DebugName; }
	protected:
		std::string m_DebugName;
	};

}