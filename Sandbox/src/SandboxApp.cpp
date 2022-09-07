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
		HZ_INFO("ExampleLayer::Update");
	}

	void OnEvent(Hazel::Event& event) override
	{
		HZ_TRACE("{0}", event);
	}
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox() 
	{
		//PushLayer(new ExampleLayer());
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