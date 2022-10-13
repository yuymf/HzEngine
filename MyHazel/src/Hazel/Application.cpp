#include "hzpch.h"															//every cpp files need to include pch!
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

//#include <GLFW/glfw3.h>
#include <glad/glad.h>

#include "Input.h"

namespace Hazel {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		HZ_CORE_ASSERT(!s_Instance, "Application already exists");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
		m_ImGuiLayer = new ImGuiLayer();
		PushOverLay(m_ImGuiLayer);
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* Layer)
	{
		m_Layerstack.PushLayer(Layer);
		Layer->OnAttach();
	}

	void Application::PushOverLay(Layer* Layer)
	{
		m_Layerstack.PushOverlay(Layer);
		Layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowsClose));  //if event 

		//HZ_CORE_TRACE("{0}", e);

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

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_Layerstack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowsClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}