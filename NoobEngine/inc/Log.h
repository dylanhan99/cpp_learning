#pragma once

#include <string>
#include <cstdarg>
#include <cstdio>
#include <iostream>

#if _MSC_VER
#include <intrin.h>
#define debugBreak() __MACHINE(__debugbreak())
#else 
#define debugBreak() __builtin_trap()
#endif

namespace NoobEngine { namespace Log {
	//const char* m_reset("\033[0m");
	enum Log_Level {
		LOG_LEVEL_TRACE = 0,
		LOG_LEVEL_DEBUG,
		LOG_LEVEL_INFO,
		LOG_LEVEL_WARN,
		LOG_LEVEL_ERROR,
		LOG_LEVEL_FATAL
	};
	static const char* Log_Color[6] = {
		"\033[0;39m",
		"\033[0;39m",
		"\033[0;32m",
		"\033[0;33m",
		"\033[0;31m",
		"\033[1;31m"
	};
	static const char* Log_Header[6] = {
		"[TRACE]: ",
		"[DEBUG]: ",
		"[INFO]: ",
		"[WARN]: ",
		"[ERROR]: ",
		"[FATAL]: "
	};
	inline static void Log_Message(Log_Level lvl, const char* fmt, ...)
	{
		char buffer[2048] = { 0 };
		va_list args;
		va_start(args, fmt);
		vsnprintf(buffer, 2048, fmt, args);
		va_end(args);

		std::cout << Log_Color[lvl];
		std::cout << Log_Header[lvl];
		std::cout << buffer;
		std::cout << "\033[0m" << std::endl;
	}
}}

void Log_Assertion_Failure(const char* expr, const char* msg, const char* file, unsigned int line);

#define MY_ASSERT(expr)													\
	{																	\
		if (expr) {}													\
		else {															\
			Log_Assertion_Failure(#expr, "", __FILE__, __LINE__);		\
			debugBreak();												\
		}																\
	}

#define MY_ASSERT_MSG(expr, msg)										\
	{																	\
		if (expr) {}													\
		else {															\
			Log_Assertion_Failure(#expr, msg, __FILE__, __LINE__);		\
			debugBreak();												\
		}																\
	}

#ifdef _DEBUG
#define MY_ASSERT_DEBUG(expr)											\
	{																	\
		if (expr) {}													\
		else {															\
			Log_Assertion_Failure(#expr, "", __FILE__, __LINE__);		\
			debugBreak();												\
		}																\
	}
#else
#define MY_ASSERT_DEBUG(expr) // do nothing if release
#endif

#ifdef _DEBUG
//#define LOG_TRACE(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_TRACE, ##__VA_ARGS__)
//#define LOG_DEBUG(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_DEBUG, ##__VA_ARGS__)
//#define LOG_INFO(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_INFO , ##__VA_ARGS__)
//#define LOG_WARN(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_WARN , ##__VA_ARGS__)
#else
//#define LOG_TRACE(...)
//#define LOG_DEBUG(...)
//#define LOG_INFO(...)
//#define LOG_WARN(...)
#endif
#define LOG_TRACE(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_TRACE, ##__VA_ARGS__)
#define LOG_DEBUG(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_DEBUG, ##__VA_ARGS__)
#define LOG_INFO(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_INFO , ##__VA_ARGS__)
#define LOG_WARN(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_WARN , ##__VA_ARGS__)
#define LOG_ERROR(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_ERROR, ##__VA_ARGS__)
#define LOG_FATAL(...)	NoobEngine::Log::Log_Message(NoobEngine::Log::LOG_LEVEL_FATAL, ##__VA_ARGS__)
