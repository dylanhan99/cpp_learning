#include "Log.h"
#include "Asserts.h"

namespace NoobEngine { namespace Log {
	
}}

void Log_Assertion_Failure(const char* expr, const char* msg, const char* file, unsigned int line)
{
	LOG_FATAL("Assertion Failure: %s, Message: '%s', File: '%s', Line: %d", expr, msg, file, line);
}