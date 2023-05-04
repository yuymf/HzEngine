#pragma once

#include <glm/glm.hpp>

namespace Hazel {

	struct HitInfo
	{
		float HitDistance;
		glm::vec3 WorldPosition;
		glm::vec3 WorldNormal;
		uint32_t EntityID;
	};

	struct Ray
	{
		glm::vec3 Origin;
		glm::vec3 Direction;
	};
}
