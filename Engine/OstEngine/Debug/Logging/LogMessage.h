#pragma once
#include <OstEngine/Debug/Logging/LogLevel.h>

#include <chrono>
#include <format>
#include <string>
#include <string_view>

// ------------------------------------------------------------

namespace ost
{
    namespace log
    {
        struct SLogMessage
        {
            template <typename... TFmtArgs>
            static SLogMessage Make( ELogLevel aVerbosity, std::string_view aFmtStr, TFmtArgs&&... aFmtArgs )
            {
                std::chrono::system_clock::now();

                return SLogMessage{ aVerbosity, std::vformat( aFmtStr, std::make_format_args( aFmtArgs... ) ),
                                    std::format( "{:%H:%M:%S}", std::chrono::floor<std::chrono::seconds>( std::chrono::system_clock::now() )), std::chrono::system_clock::now() };
                
            }

            ELogLevel Verbosity;
            std::string Message;
            std::string FormattedTime;
            std::chrono::system_clock::time_point Timestamp;
        };
    } // namespace log
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------