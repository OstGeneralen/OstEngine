// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/Logging/LogMessage.h"

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class ILogger
		{
		public: // INTERFACE
			virtual ~ILogger() = default;
			virtual void Log(const SLogMessage& msg) = 0;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------