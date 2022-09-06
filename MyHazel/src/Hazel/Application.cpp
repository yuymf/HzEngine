#include "hzpch.h"															//every cpp files need to include pch!
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* Layer)
	{
		m_Layerstack.PushLayer(Layer);
	}

	void Application::PushOverLay(Layer* Layer)
	{
		m_Layerstack.PushOverlay(Layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowsClose));  //if event 

		HZ_CORE_TRACE("{0}", e);

		for (auto it = m_Layerstack.end(); it != m_Layerstack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_Layerstack)							
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowsClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}