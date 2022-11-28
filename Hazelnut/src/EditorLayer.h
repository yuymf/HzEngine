#pragma once

#include "Hazel.h"
#include "Hazel/Panels/SceneHierarchyPanel.h"

namespace Hazel {

	class EditorLayer : public Layer
	{
	public:
		EditorLayer();
		virtual ~EditorLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		void OnUpdate(Timestep ts) override;
		virtual void OnImGuiRender() override;
		void OnEvent(Event& e) override;

	private:
		bool OnKeyPressed(KeyPressedEvent& e);

		void NewScene();
		void OpenScene();
		void SaveSceneAs();

	private:
		Hazel::OrthographicCameraController m_CameraController;

		// Temp
		Ref<VertexArray> m_SquareVA;
		Ref<Shader> m_FlatColorShader;
		Ref<Framebuffer> m_Framebuffer;

		Ref<Scene> m_ActiveScene;
		Entity m_SquareEntity;

		Entity m_PrimaryCamera;
		Entity m_SecondCamera;
		bool m_CameraPrim = true;

		Ref<Texture2D> m_CheckerboardTexture;

		bool m_ViewportFocused = false, m_ViewportHovered = false;
		glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
		glm::vec2 m_ViewportSize = { 0.0f, 0.0f };

		int m_GizmoType = -1;

		//Panels
		SceneHierarchyPanel m_SceneHierarchyPanel;
	};

}
