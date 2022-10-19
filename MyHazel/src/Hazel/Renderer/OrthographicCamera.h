#pragma once

#include <glm/glm.hpp>

namespace Hazel {

	class OrthographicCarema
	{
	public:
		OrthographicCarema() {};
		OrthographicCarema(float left, float right, float bottom, float top);

		const glm::vec3& GetProjection() const { return m_Projection; }
		void SetProjection(const glm::vec3& projection) { m_Projection = projection; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

	private:
		void RecalculateViewMatrix();

	private:
		glm::mat4 m_ProjectionMatrix;
		glm::mat4 m_ViewMatrix;
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Projection = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};

}