#pragma once
#include <random>

namespace Hazel {
	class Random
	{
	public:
		static float Float();
		static uint32_t Uint32();
		static uint64_t Uint64();
	private:
		static std::mt19937 m_RandomEngine;
		static std::uniform_int_distribution<std::mt19937::result_type> m_Distribution;
	};
}
