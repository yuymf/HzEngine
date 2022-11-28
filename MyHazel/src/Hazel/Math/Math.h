#pragma once

#include <glm/glm.hpp>

namespace Hazel::Math {

	bool DeComposeTransform(const glm::mat4& transform, glm::vec3& outranslation, glm::vec3& outRotation, glm::vec3& outScale);
}
