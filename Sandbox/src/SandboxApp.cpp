#include <Hazel.h>

class Sandbox : public Hazel::Application
{
public:
	Sandbox() {};
	~Sandbox() {};

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