// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

// ------------------------------------------------------------
// OstLogger - LogSink
// ------------------------------------------------------------
// A log sink is an "output route" for log messages. This is
// what sends the formatted log message to the desired target.
// You can implement your own by inheriting from this base 
// type or use one of the provided default sinks.
// 
// Sinks should be registered before the Logger's run is called
// ------------------------------------------------------------
#pragma once
#include "OstLog/LoggerApi.h"
#include "OstLog/LogMessage.h"

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class LOGGER_API CLogSink
		{
		public:
			CLogSink(ELogLevel levels = LOG_LEVELS_DEFAULT);
			virtual ~CLogSink() = default;
			virtual void Log(const SLogMessage& msg) = 0;

		public:
			bool FilterLogLevel(ELogLevel level) const;

		private:
			ELogLevel _levelFilter;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------