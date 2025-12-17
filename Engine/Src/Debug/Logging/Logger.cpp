#include "OstEngine/Debug/Logging/Logger.h"
#include "CoutLogging.h"

using namespace ost;
using namespace ost::log;

// ------------------------------------------------------------

CLogger& CLogger::Instance()
{
    static CLogger instance;
    return instance;
}

// ------------------------------------------------------------

void ost::log::CLogger::EnableConsoleLogging()
{
    _consoleLoggingEnabled = true;
}

// ------------------------------------------------------------

void ost::log::CLogger::PushMessage( SLogMessage&& aMsg )
{
    if (_consoleLoggingEnabled)
    {
        StdOutLog( aMsg );
    }
    _messages.emplace_back( aMsg );
}

// ------------------------------------------------------------

CLogger::LoggerIterator CLogger::begin() const
{
    return _messages.begin();
}

// ------------------------------------------------------------

CLogger::LoggerIterator CLogger::end() const
{
    return _messages.end();
}

// ------------------------------------------------------------

