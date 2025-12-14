#pragma once
#include <OstEngine/Debug/Logging/LogMessage.h>

#include <stack>
#include <string>
#include <string_view>

namespace ost
{
    namespace log
    {
        class CLogInstance
        {
        public:
            CLogInstance( const std::string& aName );

            template <typename... TArgs>
            void BeginLog( std::string_view aMsg, TArgs&&... aFmt )
            {
                BeginScope( std::move( SLogMessage::Make( ELogLevel::Message, aMsg, aFmt... ) ) );
            }

            template <typename... TArgs>
            void BeginConfirm( std::string_view aMsg, TArgs&&... aFmt )
            {
                BeginScope(  std::move(SLogMessage::Make( ELogLevel::Confirm, aMsg, aFmt... ) ) );
            }

            template <typename... TArgs>
            void BeginWarning( std::string_view aMsg, TArgs&&... aFmt )
            {
                BeginScope( std::move( SLogMessage::Make( ELogLevel::Warning, aMsg, aFmt... ) ) );
            }

            template <typename... TArgs>
            void BeginError( std::string_view aMsg, TArgs&&... aFmt )
            {
                BeginScope( std::move( SLogMessage::Make( ELogLevel::Error, aMsg, aFmt... ) ) );
            }

            template <typename... TArgs>
            void Log( std::string_view aMsg, TArgs&&... aFmt )
            {
                SLogMessage msg = SLogMessage::Make( ELogLevel::Message, aMsg, aFmt... );
                LogMessage( std::move( msg ) );
            }

            template <typename... TArgs>
            void Confirm( std::string_view aMsg, TArgs&&... aFmt )
            {
                SLogMessage msg = SLogMessage::Make( ELogLevel::Confirm, aMsg, aFmt... );
                LogMessage( std::move( msg ) );
            }

            template <typename... TArgs>
            void Warning( std::string_view aMsg, TArgs&&... aFmt )
            {
                SLogMessage msg = SLogMessage::Make( ELogLevel::Warning, aMsg, aFmt... );
                LogMessage( std::move( msg ) );
            }

            template <typename... TArgs>
            void Error( std::string_view aMsg, TArgs&&... aFmt )
            {
                SLogMessage msg = SLogMessage::Make( ELogLevel::Error, aMsg, aFmt... );
                LogMessage( std::move( msg ) );
            }

            void EndScope();

        private:
            void BeginScope( SLogMessage&& aMsg );
            void LogMessage( SLogMessage&& aMsg );

            std::string _name;
            std::stack<SLogMessage> _activeMessageStack;
        };
    } // namespace log
} // namespace ost