#pragma once

#ifdef CROC_PLATAFORM_WINDOWS
#if CR_DYNAMIC_LINK
	#ifdef CR_BUILD_DLL
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