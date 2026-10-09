// Kasper "OstGeneralen" Esbjornsson - 2026
#include "OstLog.h"
#include "OstLogMessage.h"
#include "OstLogSink.h"

#include <utility>

#include <Container/List.h>

// ------------------------------------------------------------

static ost::log::internal::Logger instance;
ost::log::internal::Logger* ost::log::internal::pLoggerInstance = &instance;

// ------------------------------------------------------------

using namespace ost;
using namespace ost::log::internal;

// ------------------------------------------------------------

Logger::Logger() = default;
Logger::~Logger() = default;

void Logger::AddSink(UniquePtr<Log::ILogSink>&& sink)
{
    _sinks.Add(std::move(sink));
}

void Logger::SendLogMessage(const LogCategory& category, ELogVerbosity verbosity, std::string&& msg) const
{
    if (category.PassVerbosity(verbosity))
    {
        const LogMessage logMsg{std::chrono::system_clock::now(), &category, verbosity, std::move(msg)};

        for (auto& sinkPtr : _sinks)
        {
            sinkPtr->Receive(logMsg);
        }
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------