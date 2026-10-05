// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <chrono>
#include <format>
#include <string>

// ------------------------------------------------------------

namespace debug
{
    // ------------------------------------------------------------

    namespace internal
    {

        enum class ELogVerbosity
        {
            Verbose,
            Message,
            Warning,
            Error,
            Critical,
        };

        // ------------------------------------------------------------

        struct LogCategory
        {
            constexpr LogCategory(std::string_view categoryName)
                : name{categoryName}
            {
            }

            std::string_view name;
        };

        // ------------------------------------------------------------

        struct LogMessage
        {
            LogMessage(const LogCategory& logCat, std::string&& msg, ELogVerbosity lvl)
                : timestamp{std::chrono::system_clock::now()}
                , pCategory{&logCat}
                , messageText{std::move(msg)}
                , verbosity{lvl}
            {
            }

            LogMessage(LogMessage&&) noexcept = default;
            LogMessage(const LogMessage&) = default;

            std::chrono::system_clock::time_point timestamp;
            const LogCategory* pCategory;
            std::string messageText;
            ELogVerbosity verbosity;
        };

        // ------------------------------------------------------------

        class Logger
        {
        public:
            static Logger& GetInstance();
            static void Shutdown();

            void PushMessage(LogMessage&& msg);

        private:
            Logger() = default;
            static Logger* _pInstance;
        };

    } // namespace internal

    static inline constexpr internal::LogCategory CreateLogCategoryStatic(std::string_view categoryName)
    {
        return internal::LogCategory{categoryName};
    }

    template <typename... TArgs>
    static inline constexpr void Log(const internal::LogCategory& category, std::string_view msg, TArgs&&... fmtArgs)
    {
        internal::Logger::GetInstance().PushMessage(internal::LogMessage{
            category,
            std::vformat(msg, std::make_format_args(fmtArgs...)),
            internal::ELogVerbosity::Message,
        });
    }

    template <typename... TArgs>
    static inline constexpr void Detail(const internal::LogCategory& category, std::string_view msg, TArgs&&... fmtArgs)
    {
        internal::Logger::GetInstance().PushMessage(internal::LogMessage{
            category,
            std::vformat(msg, std::make_format_args(fmtArgs...)),
            internal::ELogVerbosity::Verbose,
        });
    }

    template <typename... TArgs>
    static inline constexpr void Warning(const internal::LogCategory& category, std::string_view msg, TArgs&&... fmtArgs)
    {
        internal::Logger::GetInstance().PushMessage(internal::LogMessage{
            category,
            std::vformat(msg, std::make_format_args(fmtArgs...)),
            internal::ELogVerbosity::Warning,
        });
    }

    template <typename... TArgs>
    static inline constexpr void Error(const internal::LogCategory& category, std::string_view msg, TArgs&&... fmtArgs)
    {
        internal::Logger::GetInstance().PushMessage(internal::LogMessage{
            category,
            std::vformat(msg, std::make_format_args(fmtArgs...)),
            internal::ELogVerbosity::Error,
        });
    }

} // namespace debug

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------