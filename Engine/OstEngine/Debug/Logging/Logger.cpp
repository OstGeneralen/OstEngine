#include "Logger.h"

using namespace ost;
using namespace ost::log;

// ------------------------------------------------------------

CLogger& CLogger::Instance()
{
    static CLogger instance;
    return instance;
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

