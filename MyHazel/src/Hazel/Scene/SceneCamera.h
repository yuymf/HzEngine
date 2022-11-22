#pragma once

#include "Hazel/Scene/Camera.h"

namespace Hazel {

	class SceneCamera : public Camera
	{
	public:
		SceneCamera();
		virtual ~SceneCamera() = default;

		float GetOrthographicSize() const { return m_OrthographicSize; }

		void SetOrthographic(float size, float nearClip, float farClip);
		void SetViewport(uint32_t width, uint32_t height);
		void SetOrthographicSize(float size) { m_OrthographicSize = size; RecalculateProjection(); }

	private:
		void RecalculateProjection();

	private:
		float m_OrthographicSize = 10.0f;
		float m_OrthographicNear = -1.0f, m_OrthographicFar = 1.0f;

		float m_AspectRatio = 0.0f;
	};

}