#pragma once
#include "Hazel.h"
#include <ImGui/imgui.h>
#include "Hazel/RayTracing/RayTracingScene.h"

namespace Hazel {
	class RayTracingLayer :public Layer
	{
	public:
		RayTracingLayer();
		virtual void OnUpdate(Timestep ts) override;
		virtual void OnAttach() override;
		virtual void OnImGuiRender() override;

	private:
		ImVec2 m_RenderViewPortSize;

		Ref<RayTracingCamera> m_Camera;
		Ref<RayTracingScene> m_Scene;
		Ref<Timer> m_Timer;
		float m_LastRenderTime;
	};
}
