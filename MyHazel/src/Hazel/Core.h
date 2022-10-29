#pragma once

#include <memory>

#ifdef HZ_PLATFORM_WINDOWS
#if HZ_DYNAMIC_DLL
	#ifdef HZ_BUILD_DLL
		#define HAZEL_API _declspec(dllexport)
	#else
		#define HAZEL_API _declspec(dllimport)
	#endif
#else
	#define HAZEL_API
#endif
#else
	#error Hazel only supports Windows!
#endif

#ifdef HZ_ENABLE_ASSERTS                                                   //FOR DEBUG
	#define HZ_ASSERT(x, ...) {if(!(x)) { HZ_ERROR("Assertion Failed : {0}", __VA_ARGS__); __debugbreak(); } }
	#define HZ_CORE_ASSERT(x, ...) {if(!(x)) { HZ_CORE_ERROR("Assertion Failed : {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define HZ_ASSERT(x, ...)
	#define HZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BIND_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Hazel {

	template<typename T>
	using Ref = std::shared_ptr<T>;

	template<typename T>
	using Scope = std::unique_ptr<T>;
}