#pragma once
#include <OstEngine/Debug/Logging/LogLevel.h>
#include <OstEngine/Debug/Logging/LogMessage.h>

#include <vector>

// ------------------------------------------------------------

namespace ost
{
    class Logging;

    namespace log
    {
        class CLogger
        {
            friend Logging;

        public:
            using LoggerIterator = std::vector<SLogMessage>::const_iterator;

        public:
            static CLogger& Instance();
            // Allow iterating the messages via range-for
            LoggerIterator begin() const;
            LoggerIterator end() const;

        private:
            CLogger() = default;
            std::vector<SLogMessage> _messages;
        };

    } // namespace log

    // Utility Class for easier access
    class Logging
    {
    public:
        template <typename... TFmt>
        static void Log( std::string_view aStr, TFmt&&... aFmt );

        template <typename... TFmt>
        static void Confirm( std::string_view aStr, TFmt&&... aFmt );

        template <typename... TFmt>
        static void Warning( std::string_view aStr, TFmt&&... aFmt );

        template <typename... TFmt>
        static void Error( std::string_view aStr, TFmt&&... aFmt );
    };

    template <typename... TFmt>
    inline void ost::Logging::Log( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance()._messages.emplace_back(
            log::SLogMessage::Make( log::ELogLevel::Message, aStr, aFmt... ) );
    }

    template <typename... TFmt>
    inline void ost::Logging::Confirm( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance()._messages.emplace_back(
            log::SLogMessage::Make( log::ELogLevel::Confirm, aStr, aFmt... ) );
    }

    template <typename... TFmt>
    inline void ost::Logging::Warning( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance()._messages.emplace_back(
            log::SLogMessage::Make( log::ELogLevel::Warning, aStr, aFmt... ) );
    }

    template <typename... TFmt>
    inline void ost::Logging::Error( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance()._messages.emplace_back(
            log::SLogMessage::Make( log::ELogLevel::Error, aStr, aFmt... ) );
    }
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
