#pragma once

#include <memory>

#ifdef _WIN32
	#ifdef _WIN64
		#define CROC_PLATAFORM_WINDOWS
	#else
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>

	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define CROC_PLATAFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC == 1
		#define CROC_PLATAFORM_MACOS
		#error "MacOS is not supported!"
#else
	#error "Unkown Apple plataform!"
#endif

#elif defined(__ANDROID__)
	#define CROC_PLATFORM_ANDROID
	#error "Android is not supported!"

#elif defined(__linux__)
	#define CROC_PLATFORM_LINUX
	#error "Linux is not supported!"
#else
	#error "Unknown platform!"
#endif 

#ifdef CROC_PLATAFORM_WINDOWS
	#if CROC_DYNAMIC_LINK
		#ifdef CROC_BUILD_DLL
			#define CROC_API __declspec(dllexport)
		#else
			#define CROC_API __declspec(dllimport)
		#endif
	#else
		#define CROC_API
#endif
#else
	#error Croc only supports Windows!
#endif 

#ifdef CR_DEBUG
	#define CROC_ENABLE_ASSERTS
#endif

#ifdef CROC_ENABLE_ASSERTS
	#define CROC_ASSERT(x, ...) {if(!(x)) { CROC_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define CROC_CORE_ASSERT(x, ...) {if(!(x)) { CROC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define CROC_ASSERT(x, ...)
	#define CROC_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define CROC_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Croc{

	template<typename T>
	using Scope = std::unique_ptr<T>;
	
	template<typename T>
	using Ref = std::shared_ptr<T>;
}