// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/APIDefinition.h"
#include "OstLog/Logging/LogLevel.h"
#include "OstLog/Logging/LogMessage.h"
#include <string>

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		struct LOGGER_API SMessageFormatter
		{
			SMessageFormatter(const SLogMessage& msg);
			std::string LevelStr_Full() const;
			std::string LevelStr_Abbr() const;
			std::string TimeStr_HHMMSS() const;
			std::string TimeStr_HHMMSSMSMS() const;
			std::string MessageStr() const;
		private:
			const SLogMessage& _msg;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------