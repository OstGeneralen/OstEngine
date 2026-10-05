// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "OstLog.h"

#include <chrono>
#include <string>

// ------------------------------------------------------------

namespace ost::log::internal
{
    struct LogMessage
    {
        std::chrono::system_clock::time_point timeStamp;
        const LogCategory* pCategory;
        ELogVerbosity verbosity;
        std::string message;
    };
} // namespace ost::log

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------