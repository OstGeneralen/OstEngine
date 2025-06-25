// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/Logging/LogLevel.h"

#include <chrono>
#include <functional>
#include <source_location>
#include <string_view>
#include <vector>

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		struct SLogMessage
		{
			std::chrono::system_clock::time_point Timestamp;
			ELogLevel Level;
			std::source_location Source;
			std::string_view LoggerName;
			std::function<std::string()> MessageFormatter;
			std::vector<SLogMessage> SubMessages;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------