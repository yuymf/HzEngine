#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"

namespace Hazel {

	class Hazelnut : public Application
	{
	public:
		Hazelnut()
			: Application("WhyU Editor")
		{
			//PushLayer(new ExampleLayer());
			PushLayer(new EditorLayer());
		}

		~Hazelnut() {}

	};

	Application* CreateApplication() {
		return new Hazelnut();
	};
}