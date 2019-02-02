#pragma once

#ifdef COG_PLATFORM_WINDOWS
	#ifdef COG_BUILD_DLL
        #define COG_API __declspec(dllexport)
	#else
        #define COG_API __declspec(dllimport)
	#endif
#else
	#error COG only supports Windows!
#endif

constexpr inline unsigned char bit(unsigned char x) noexcept { return 1 << x; }