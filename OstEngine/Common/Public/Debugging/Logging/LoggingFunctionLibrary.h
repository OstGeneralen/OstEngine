// OstEngine Code - Copyright (c) Kasper Esbjornsson 2022

#pragma once
#include <string>
#include <format>
#include "Common/Public/Debugging/Logging/Verbosity.h"
#include "Common/Public/Debugging/Logging/ConsoleColors.h"

namespace ost
{
	namespace logging
	{
		extern std::string VerbosityToString(ELogVerbosity v); // Defined in LoggingFunctionLibrary.cpp
		extern int GetConsoleColorCode(EConsoleColor c); // Defined in LoggingFunctionLibrary.cpp
		extern void SetConsoleColor(int code);
	}
}
