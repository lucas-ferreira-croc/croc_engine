#pragma once

#ifdef CROC_PLATAFORM_WINDOWS
	#ifdef CR_BUILD_DLL
		#define CROC_API __declspec(dllexport)	
	#else
		#define CROC_API __declspec(dllimport)	
	#endif
#else
	#error Croc only supports Windows!
#endif

#define BIT(x) (1 << x)