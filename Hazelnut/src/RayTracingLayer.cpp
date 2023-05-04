#include "RayTracingLayer.h"
#include <ImGui/imgui.h>
#include "Hazel/RayTracing/RayTracingRenderImage.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Hazel {

	RayTracingLayer::RayTracingLayer()
		: m_RenderViewPortSize(ImVec2(0.0f, 0.0f)), m_Camera(CreateRef<RayTracingCamera>(45.0f, 0.1f, 100.0f)),
		m_Scene(CreateRef<RayTracingScene>()), m_Timer(CreateRef<Timer>()), m_LastRenderTime(0.f)
	{
		// Submit Sphere Here
		{
			auto material = CreateRef<Material>();
			material->SetAlbedo(glm::vec3(1.f, 0.f, 1.f));

			auto addedSphere = CreateRef<Sphere>(glm::vec3(0.0f, 0.0f, 0.0f), 1.0f, 0);
			addedSphere->SetMaterial(material);

			m_Scene->AddSphere(addedSphere);
		}
		{
			auto material = CreateRef<Material>();
			material->SetAlbedo(glm::vec3(0.2f, 0.3f, 1.f));

			auto addedSphere = CreateRef<Sphere>(glm::vec3(1.f, -101.f, -5.f), 100.f, 1);
			addedSphere->SetMaterial(material);

			m_Scene->AddSphere(addedSphere);
		}	
	}

	void RayTracingLayer::OnUpdate(Timestep ts)
	{
		m_Timer->Reset();
		if (m_RenderViewPortSize.x > 0 && m_RenderViewPortSize.y > 0)
		{
			m_Camera->OnResize(m_RenderViewPortSize.x, m_RenderViewPortSize.y);
			m_Camera->OnUpdate(ts);

			m_Scene->OnViewPortResize(m_RenderViewPortSize.x, m_RenderViewPortSize.y);
			m_Scene->OnUpdate(ts, m_Camera);
		}

		m_LastRenderTime = m_Timer->ElapsedMillis();
	}

	void RayTracingLayer::OnAttach()
	{

	}


	void RayTracingLayer::OnImGuiRender()
	{
		static bool opt_dockSpaceOpen = true;
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->Pos);
			ImGui::SetNextWindowSize(viewport->Size);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become unDocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockSpace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &opt_dockSpaceOpen, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// DockSpace
		ImGuiIO& io = ImGui::GetIO();
		ImGuiStyle& style = ImGui::GetStyle();
		float minWinSizeX = style.WindowMinSize.x;
		style.WindowMinSize.x = 370.f;
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		style.WindowMinSize.x = minWinSizeX;
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					Application::Get().Close();
				}
				ImGui::EndMenu();
			}

			ImGui::EndMenuBar();
		}

		// UI: Settings------------------------------------------------------------------------------------------
		ImGui::Begin("Settings");
		ImGui::Text("Last render: %.3fms", m_LastRenderTime);
		if (ImGui::Button("Render"))
		{
			// Render();
		}
		ImGui::End();
		// -----------------------------------------------------------------------------------------------------
		
		// UI: Scene--------------------------------------------------------------------------------------------
		ImGui::Begin("Scene");
		auto& vecSphere = m_Scene->GetSpheres();
		for (auto i = 0; i < vecSphere.size(); i++)
		{
			ImGui::PushID(i);
			ImGui::DragFloat3("Position", glm::value_ptr(vecSphere[i]->GetPosition()), 0.1f);
			ImGui::DragFloat("Radius", &vecSphere[i]->GetRadius(), 0.1f);
			ImGui::ColorEdit3("Albedo", glm::value_ptr(vecSphere[i]->GetMaterial()->GetAlbedo()));
			ImGui::Separator();
			ImGui::PopID();
		}
		ImGui::End();
		// -----------------------------------------------------------------------------------------------------

		// UI: ViewPort-----------------------------------------------------------------------------------------
		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

		ImGui::Begin("ViewPort");

		m_RenderViewPortSize = ImGui::GetContentRegionAvail();

		auto image = m_Scene->GetRenderImage();
		if (image > 0)
		{
			ImGui::Image((void*)image, m_RenderViewPortSize, ImVec2(0, 1), ImVec2(1, 0));
		}

		ImGui::End();
		ImGui::PopStyleVar();
		// -----------------------------------------------------------------------------------------------------

		ImGui::End();
	}
}
