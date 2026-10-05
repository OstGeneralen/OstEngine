// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "OstLog.h"
#include "OstLogMessage.h"

// ------------------------------------------------------------

namespace Log
{
    class ILogSink
    {
    public:
        virtual ~ILogSink() = default;
        virtual void Receive(const Message& msg) = 0;

    protected:
        constexpr static inline std::string_view GetVerbosityStringAbbr(EVerbosity v) noexcept
        {
            switch (v)
            {
            case EVerbosity::Verbose:
                return "VRB";
            case EVerbosity::Message:
                return "MSG";
            case EVerbosity::Warning:
                return "WRN";
            case EVerbosity::Error:
                return "ERR";
            case EVerbosity::Critical:
                return "CRT";
            }
            return "";
        }
        constexpr static inline std::string_view GetVerbosityStringLong(EVerbosity v) noexcept
        {
            switch (v)
            {
            case EVerbosity::Verbose:
                return "VERBOSE";
            case EVerbosity::Message:
                return "MESSAGE";
            case EVerbosity::Warning:
                return "WARNING";
            case EVerbosity::Error:
                return "ERROR";
            case EVerbosity::Critical:
                return "CRITICAL";
            }
            return "";
        }
    };
} // namespace Log

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------