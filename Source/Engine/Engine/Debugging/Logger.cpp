// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Logger.h"

#include <iostream>

// ------------------------------------------------------------

using namespace debug;
using namespace debug::internal;

// ------------------------------------------------------------

Logger* Logger::_pInstance = nullptr;

Logger& Logger::GetInstance()
{
    if (_pInstance == nullptr)
    {
        _pInstance = new Logger();
    }

    return *_pInstance;
}

// ------------------------------------------------------------

void Logger::Shutdown()
{
    delete _pInstance;
    _pInstance = nullptr;
}

// ------------------------------------------------------------

void Logger::PushMessage(LogMessage&& msg)
{
    switch (msg.verbosity)
    {
    case ELogVerbosity::Verbose:
        std::cout << "[VRB]: ";
        break;
    case ELogVerbosity::Message:
        std::cout << "[MSG]: ";
        break;
    case ELogVerbosity::Warning:
        std::cout << "[WRN]: ";
        break;
    case ELogVerbosity::Error:
        std::cout << "[ERR]: ";
        break;
    case ELogVerbosity::Critical:
        std::cout << "[CRT]: ";
        break;
    }
    std::cout << msg.messageText << " (" << std::string(msg.pCategory->name) << ")" << std::endl;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------