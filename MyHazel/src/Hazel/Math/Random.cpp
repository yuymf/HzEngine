#include "hzpch.h"
#include "Random.h"
#include <limits>

namespace Hazel {
	std::mt19937 Random::m_RandomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> Random::m_Distribution;

	float Random::Float()
	{
		return static_cast<float>(m_Distribution(m_RandomEngine)) / static_cast<float>(std::numeric_limits<uint32_t>::max());
	}

	uint32_t Random::Uint32()
	{
		return static_cast<uint32_t>(m_Distribution(m_RandomEngine));
	}

	uint64_t Random::Uint64()
	{
		return static_cast<uint64_t>(m_Distribution(m_RandomEngine));
	}
}
