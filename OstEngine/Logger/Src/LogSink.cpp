// OstEngine - Copyright(c) 2025 Kasper Esbj�rnsson (MIT License)

#include "OstLog/Sinks/LogSink.h"

// ------------------------------------------------------------

ost::log::CLogSink::CLogSink(ELogLevel levels)
	: _levelFilter{levels}
{
}

// ------------------------------------------------------------

bool ost::log::CLogSink::FilterLogLevel(ELogLevel level) const
{
	return (level & _levelFilter) != ELogLevel::NONE;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------