#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "Sandbox2D.h"

#include "ExampleLayer.h"

namespace Hazel {

	class Sandbox : public Application
	{
	public:
		Sandbox(ApplicationCommandLineArgs args)
			: Application("WhyU", args)
		{
			// PushLayer(new ExampleLayer());
			PushLayer(new Sandbox2D());
		}

		~Sandbox() {}

	};

	Application* CreateApplication(ApplicationCommandLineArgs args) {
		return new Sandbox(args);
	};
}

