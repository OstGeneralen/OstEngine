// OstEngine Code - Copyright (c) Kasper Esbjornsson 2022

#pragma once
#include "Common/Public/Debugging/Logging/DefaultLogger.h"


#define DEFINE_LOG( LogName ) ost::CDefaultLogger LogName##(#LogName)
#define LOG_VERBOSE( Logger, Msg, ... ) Logger##.Log( ost::ELogVerbosity::Verbose, Msg, __VA_ARGS__ )
#define LOG_MESSAGE( Logger, Msg, ... ) Logger##.Log( ost::ELogVerbosity::Log, Msg, __VA_ARGS__ )
#define LOG_CONFIRM( Logger, Msg, ... ) Logger##.Log( ost::ELogVerbosity::Confirm, Msg, __VA_ARGS__ )
#define LOG_WARNING( Logger, Msg, ... ) Logger##.Log( ost::ELogVerbosity::Warning, Msg, __VA_ARGS__ )
#define LOG_ERROR( Logger, Msg, ... ) Logger##.Log( ost::ELogVerbosity::Error, Msg, __VA_ARGS__ )

#define ERROR_RETURN_IF( Condition, Logger, Msg, ... ) if( Condition ) { Logger##.Log( ost::ELogVerbosity::Error, Msg, __VA_ARGS__ ); return; }
#define ERROR_RETURN_VAL_IF( Condition, Val, Logger, Msg, ... ) if( Condition ) { Logger##.Log( ost::ELogVerbosity::Error, Msg, __VA_ARGS__ ); return Val##; }
