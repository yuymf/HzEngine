#pragma once

#include <glm/glm.hpp>

struct TransformComponent
{
	glm::mat4 Transform{ 1.0f };

	TransformComponent() = default;
	TransformComponent(const TransformComponent&) = default;
	TransformComponent(const glm::mat4& transform)
		: Transform(transform) {}

	// operator: TransformComponent equals glm::mat4&; used in Has && Get;
	operator glm::mat4& () { return Transform; }
	operator const glm::mat4& () const { return Transform; }
};

struct SpriteRendererComponent
{
	glm::vec4 Color{ 1.0f, 1.0f, 1.0f, 1.0f };

	SpriteRendererComponent() = default;
	SpriteRendererComponent(const SpriteRendererComponent&) = default;
	SpriteRendererComponent(const glm::vec4& color)
		: Color(color) {}
};