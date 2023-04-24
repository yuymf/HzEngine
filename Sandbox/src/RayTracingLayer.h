#pragma once

#include "Hazel.h"
#include <ImGui/imgui.h>

namespace Hazel {
	class RayTracingLayer : public Layer
	{
	public:
		RayTracingLayer();
		virtual void OnAttach() override;
		virtual void OnImGuiRender() override;
	private:
		void Render();
	private:
		ImVec2 m_vec2RenderViewPortSize;
		Ref<Image> m_Image;

		Ref<Timer> m_Timer;
		float m_LastRenderTime;
	};
}


