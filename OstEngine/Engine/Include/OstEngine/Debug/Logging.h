// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Debug/Logging/LoggingContext.h"
#include "OstEngine/Debug/Logging/LogMessage.h"

// ------------------------------------------------------------

#define LOG_MESSAGE( msgStr, ... ) ost::CLoggingContext::PushLogMessage( ost::SLogMessage( ost::FormatString(msgStr, __VA_ARGS__ ), ost::ELogLevel::Log))
#define LOG_INFO( msgStr, ... ) ost::CLoggingContext::PushLogMessage( ost::SLogMessage( ost::FormatString(msgStr, __VA_ARGS__ ), ost::ELogLevel::Info))

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------