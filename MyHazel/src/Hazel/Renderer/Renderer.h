#pragma once

#include "RenderCommand.h"
#include "Hazel/Renderer/Shader.h"

#include "Hazel/Renderer/OrthographicCamera.h"

namespace Hazel {

	class Renderer
	{
	public:
		static void BeginScene(OrthographicCarema& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

	private:
		struct SceneData
		{
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}