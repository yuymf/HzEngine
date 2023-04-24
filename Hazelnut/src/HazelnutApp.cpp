#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>

#include "EditorLayer.h"
#include "RayTracingLayer.h"

namespace Hazel {

	class Hazelnut : public Application
	{
	public:
		Hazelnut(ApplicationCommandLineArgs args)
			: Application("WhyU Editor", args)
		{
			//PushLayer(new EditorLayer());
			PushLayer(new RayTracingLayer());
		}

		~Hazelnut() {}

	};

	Application* CreateApplication(ApplicationCommandLineArgs args) {
		return new Hazelnut(args);
	};
}
