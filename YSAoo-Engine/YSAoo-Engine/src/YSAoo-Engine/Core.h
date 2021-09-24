#pragma once
namespace YSAoo {

#ifdef YSA_PLATFORM_WINDOWS
	#ifdef YSA_BUILD_DLL
		#define YSAoo_API _declspec(dllexport)
	#else
		#define YSAoo_API _declspec(dllimport)
	#endif
#else
	#error Only Windows Supported!!!
#endif

#define BIT(x) (1<<x)
}