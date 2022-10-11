#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer()
		:Layer("Example")
	{
	}

	void OnUpdate() override
	{
		//HZ_INFO("ExampleLayer::Update");

		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
		{
			HZ_INFO("Tab key is pressed!");
		}
	}

	void OnEvent(Hazel::Event& event) override
	{
		// HZ_TRACE("{0}", event);
		if (event.GetEventType() == Hazel::EventType::KeyPressed) {
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox() 
	{
		PushLayer(new ExampleLayer());
		PushOverLay(new Hazel::ImGuiLayer());
	}
	~Sandbox() {}

};

//namespace Hazel {                      --------use core.h to auto set imp&exp within ifdef
//
//	_declspec(dllimport) void Print();
//}

// void main()						    ---------use EntryPoint.h to make main() there
//{
//  Sandbox* sandbox = new Sandbox;
//	app->Run();
//	delete app;
//}

Hazel::Application* Hazel::CreateApplication() {
	return new Sandbox;
};