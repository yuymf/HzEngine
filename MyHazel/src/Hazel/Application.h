#pragma once

#include "Core.h"
#include "Events/Event.h"

#include "Events/ApplicationEvent.h"
#include "Window.h"
#include "LayerStack.h"

namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* Layer);
		void PushOverLay(Layer* Layer);

	private:
		bool OnWindowsClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_Layerstack;

	};

	//To define in client;
	Application* CreateApplication();

}
