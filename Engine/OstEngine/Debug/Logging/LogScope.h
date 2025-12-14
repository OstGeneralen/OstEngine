#pragma once
#include <OstEngine/Types.h>

#include <format>
#include <string>
#include <string_view>
#include <vector>

namespace ost
{
    namespace log
    {
        struct SScopedMessage
        {
            Int32 depth;
            std::string content;
        };

        struct SLogScope
        {
        public:
            SLogScope() = default;
            template <typename... TFmtArgs>
            SLogScope( std::string_view aMsg, TFmtArgs&&... aFmt )
                : _currentDepth{ 0 }
                , _topMessage{ std::vformat( aMsg, std::make_format_args( aFmt... ) ) }
                , _subMessages{}
            {
            }
            SLogScope( const SLogScope& ) = default;
            SLogScope( SLogScope&& ) noexcept = default;

            template <typename... TFmtArgs>
            void AddMessage( std::string_view aFmt, TFmtArgs&&... aFmtArgs )
            {
                _subMessages.push_back( { _currentDepth, std::vformat( aFmt, std::make_format_args( aFmtArgs... ) ) } );
            }

            void PushLevel();
            void PopLevel();

            void Log();
            void Confirm();
            void Warning();
            void Error();

            template <typename... TFmtArgs>
            void Log( std::string_view aFmt, TFmtArgs&&... aFmtArgs )
            {
                AddMessage( aFmt, aFmtArgs... );
                Log();
            }

            template <typename... TFmtArgs>
            void Confirm( std::string_view aFmt, TFmtArgs&&... aFmtArgs )
            {
                AddMessage( aFmt, aFmtArgs... );
                Confirm();
            }

            template <typename... TFmtArgs>
            void Warning( std::string_view aFmt, TFmtArgs&&... aFmtArgs )
            {
                AddMessage( aFmt, aFmtArgs... );
                Warning();
            }

            template <typename... TFmtArgs>
            void Error( std::string_view aFmt, TFmtArgs&&... aFmtArgs )
            {
                AddMessage( aFmt, aFmtArgs... );
                Error();
            }

        private:
            void GenerateString( std::string& aOutStr );

            Int32 _currentDepth;
            std::string _topMessage;
            std::vector<SScopedMessage> _subMessages;
        };

    } // namespace log
} // namespace ost