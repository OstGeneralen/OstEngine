// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Debug/Logging/LoggingContext.h"
#include "OstEngine/Debug/Logging/LogMessage.h"

// ------------------------------------------------------------

#define LOG_BEGIN_SCOPE() ost::CLoggingContext::OpenScope()
#define LOG_END_SCOPE() ost::CLoggingContext::CloseScope()

#define LOG_DETAIL( msgStr, ... ) ost::CLoggingContext::PushLogMessage( ost::SLogMessage( ost::FormatString(msgStr, __VA_ARGS__ ), ost::ELogLevel::Verbose))
#define LOG_MESSAGE( msgStr, ... ) ost::CLoggingContext::PushLogMessage( ost::SLogMessage( ost::FormatString(msgStr, __VA_ARGS__ ), ost::ELogLevel::Log))
#define LOG_INFO( msgStr, ... ) ost::CLoggingContext::PushLogMessage( ost::SLogMessage( ost::FormatString(msgStr, __VA_ARGS__ ), ost::ELogLevel::Info))
#define LOG_CONFIRM( msgStr, ... ) ost::CLoggingContext::PushLogMessage( ost::SLogMessage( ost::FormatString(msgStr, __VA_ARGS__ ), ost::ELogLevel::Confirm))
#define LOG_WARNING( msgStr, ... ) ost::CLoggingContext::PushLogMessage( ost::SLogMessage( ost::FormatString(msgStr, __VA_ARGS__ ), ost::ELogLevel::Warning))
#define LOG_ERROR( msgStr, ... ) ost::CLoggingContext::PushLogMessage( ost::SLogMessage( ost::FormatString(msgStr, __VA_ARGS__ ), ost::ELogLevel::Error))

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------