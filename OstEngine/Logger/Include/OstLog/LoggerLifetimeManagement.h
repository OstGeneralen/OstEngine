// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/LoggerApi.h"

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class CLogSink;
	}
}

extern "C" LOGGER_API void OstLogger_RegisterLogSink(ost::log::CLogSink& sink);
extern "C" LOGGER_API void OstLogger_RunLogger();
extern "C" LOGGER_API void OstLogger_PostShutdownSignal();
extern "C" LOGGER_API void OstLogger_AwaitShutdown();

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------