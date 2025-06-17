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

// Register a new log sink (output) with the logger instance.
// Note: The sink provided is expected to share lifetime with the logger's runtime
extern "C" LOGGER_API void OstLogger_RegisterLogSink(ost::log::CLogSink& sink);

// Start the logging background thread
extern "C" LOGGER_API void OstLogger_RunLogger();

// Notify the logging background thread that shutdown is requested
extern "C" LOGGER_API void OstLogger_PostShutdownSignal();

// Await and join the logging background thread with the calling thread
// Note: Always call this after PostShutdownSignal
// Note: This should be called by the same thread as OstLogger_RunLogger
extern "C" LOGGER_API void OstLogger_AwaitShutdown();

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------