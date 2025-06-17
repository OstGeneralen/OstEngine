// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/Sinks/LogSink.h"

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class CConsoleLogSink final : public CLogSink
		{
		public:
			CConsoleLogSink(ELogLevel levels = LOG_LEVELS_DEFAULT);
			void Log(const SLogMessage& msg) override;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------