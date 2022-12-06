#pragma once

#if _MSC_VER
#include <intrin.h>
#define debugBreak() __debugBreak()
#else 
#define debugBreak() __builtin_trap()
#endif

void Log_Assertion_Failure(const char* expr, const char* msg, const char* file, unsigned int line);

#define MY_ASSERT(expr)												  \
	{																  \
		if (expr) {													  \
		} else { 													  \
			Log_Assertion_Failure(#expr, "", __FILE__, __LINE__);	  \
		} 															  \
	}
