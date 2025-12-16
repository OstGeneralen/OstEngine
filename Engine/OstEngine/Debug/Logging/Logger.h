#pragma once
#include <OstEngine/Debug/Logging/LogLevel.h>
#include <OstEngine/Debug/Logging/LogMessage.h>
#include <OstEngine/Debug/Logging/LogScope.h>

#include <vector>

// ------------------------------------------------------------

namespace ost
{
    class Logging;
    class CLogInstance;

    namespace log
    {
        class CLogger
        {
        public:
            using LoggerIterator = std::vector<SLogMessage>::const_iterator;

        public:
            static CLogger& Instance();

            void EnableConsoleLogging();

            // Allow iterating the messages via range-for
            LoggerIterator begin() const;
            LoggerIterator end() const;

            void PushMessage( SLogMessage&& aMsg );

        private:
            CLogger() = default;
            std::vector<SLogMessage> _messages;
            bool _consoleLoggingEnabled = false;
        };

    } // namespace log

    // Utility Class for easier access
    class Logging
    {
    public:
        template <typename... TFmt>
        static log::SLogScope BeginLogScope( std::string_view aStr, TFmt&&... aFmt );

        template <typename... TFmt>
        static void Detail( std::string_view aStr, TFmt&&... aFmt );

        template <typename... TFmt>
        static void Log( std::string_view aStr, TFmt&&... aFmt );

        template <typename... TFmt>
        static void Info( std::string_view aStr, TFmt&&... aFmt );

        template <typename... TFmt>
        static void Confirm( std::string_view aStr, TFmt&&... aFmt );

        template <typename... TFmt>
        static void Warning( std::string_view aStr, TFmt&&... aFmt );

        template <typename... TFmt>
        static void Error( std::string_view aStr, TFmt&&... aFmt );
    };

    template <typename... TFmt>
    inline log::SLogScope ost::Logging::BeginLogScope( std::string_view aStr, TFmt&&... aFmt )
    {
        return log::SLogScope( aStr, aFmt... );
    }

    template <typename... TFmt>
    inline void ost::Logging::Detail( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance().PushMessage( log::SLogMessage::Make( log::ELogLevel::Detail, aStr, aFmt... ) );
    }

    template <typename... TFmt>
    inline void ost::Logging::Log( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance().PushMessage( log::SLogMessage::Make( log::ELogLevel::Message, aStr, aFmt... ) );
    }

    template <typename... TFmt>
    inline void ost::Logging::Info( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance().PushMessage( log::SLogMessage::Make( log::ELogLevel::Info, aStr, aFmt... ) );
    }

    template <typename... TFmt>
    inline void ost::Logging::Confirm( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance().PushMessage( log::SLogMessage::Make( log::ELogLevel::Confirm, aStr, aFmt... ) );
    }

    template <typename... TFmt>
    inline void ost::Logging::Warning( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance().PushMessage( log::SLogMessage::Make( log::ELogLevel::Warning, aStr, aFmt... ) );
    }

    template <typename... TFmt>
    inline void ost::Logging::Error( std::string_view aStr, TFmt&&... aFmt )
    {
        log::CLogger::Instance().PushMessage( log::SLogMessage::Make( log::ELogLevel::Error, aStr, aFmt... ) );
    }
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
