// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <format>
#include <string>
#include <string_view>

#include <Container/List.h>
#include <Memory/UniquePtr.h>
#include <Utility/Assert.h>

// ------------------------------------------------------------
// Forward Declarations
// ------------------------------------------------------------

namespace ost::log::internal
{
    class LogCategory;
    class Logger;
    struct LogMessage;

    extern Logger* pLoggerInstance;

    enum class ELogVerbosity
    {
        Verbose,
        Message,
        Warning,
        Error,
        Critical,
    };
} // namespace ost::log::internal

namespace Log
{
    class ILogSink;
    typedef ost::log::internal::LogCategory Category;
    typedef ost::log::internal::LogMessage Message;
    typedef ost::log::internal::ELogVerbosity EVerbosity;

    /// @brief Create a new static category for log messages to be send through
    /// @param name The readable name of the category
    /// @param verbosity The lowest verbosity that this category will actually log
    /// @return Category to be immediately moved into your static instance
    [[nodiscard]] constexpr static Category NewCategory(std::string_view name, EVerbosity verbosity = EVerbosity::Verbose);

    // ------------------------------------------------------------

    /// @brief Log a verbose message
    /// @tparam ...TArgs
    /// @param c The category to log this message under
    /// @param fmtStr The format string of this message
    /// @param ...fmtArgs The format args of this message
    template <typename... TArgs>
    void Verbose(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs);

    /// @brief Log a standard verbosity message
    /// @tparam ...TArgs
    /// @param c The category to log this message under
    /// @param fmtStr The format string of this message
    /// @param ...fmtArgs The format args of this message
    template <typename... TArgs>
    void Log(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs);

    /// @brief Log a warning message
    /// @tparam ...TArgs
    /// @param c The category to log this message under
    /// @param fmtStr The format string of this message
    /// @param ...fmtArgs The format args of this message
    template <typename... TArgs>
    void Warning(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs);

    /// @brief Log an error message
    /// @tparam ...TArgs
    /// @param c The category to log this message under
    /// @param fmtStr The format string of this message
    /// @param ...fmtArgs The format args of this message
    template <typename... TArgs>
    void Error(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs);

    /// @brief Log a critical message
    /// @tparam ...TArgs
    /// @param c The category to log this message under
    /// @param fmtStr The format string of this message
    /// @param ...fmtArgs The format args of this message
    template <typename... TArgs>
    void Critical(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs);

    /// @brief Assert the given condition and log the provided message if the assertion fails.
    /// @note The verbosity of the message if the assertion fails will be Critical
    /// @tparam ...TArgs
    /// @param condition The condition to assert is true
    /// @param c The category to log this message under
    /// @param fmtStr The format string of this message
    /// @param ...fmtArgs The format args of this message
    template <typename... TArgs>
    void Assert(bool condition, const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs);

} // namespace Log

// ------------------------------------------------------------

class ost::log::internal::LogCategory
{
public:
    constexpr LogCategory(std::string_view n, ELogVerbosity v) noexcept
        : _name{n}
        , _verbosity{v}
    {
    }

    constexpr LogCategory(const LogCategory&) noexcept = default;
    constexpr LogCategory& operator=(const LogCategory&) noexcept = default;

    constexpr std::string_view GetName() const noexcept
    {
        return _name;
    }
    constexpr ELogVerbosity GetVerbosity() const noexcept
    {
        return _verbosity;
    }

    constexpr bool PassVerbosity(ELogVerbosity v) const noexcept
    {
        return v >= _verbosity;
    }

    void SetVerbosityLevel(ELogVerbosity v)
    {
        _verbosity = v;
    }

private:
    std::string_view _name;
    ELogVerbosity _verbosity;
};

// ------------------------------------------------------------

class ost::log::internal::Logger
{
public:
    Logger();
    ~Logger();

    void AddSink(UniquePtr<Log::ILogSink>&& sink);
    void PostMessage(const LogCategory& category, ELogVerbosity verbosity, std::string&& msg) const;

private:
    // No actual state change, mutable to allow us to forwar the message to the non-const Receive of the sink
    // while keeping the PostMessage function const
    mutable List<UniquePtr<Log::ILogSink>> _sinks;
};

// ------------------------------------------------------------

inline constexpr Log::Category Log::NewCategory(std::string_view name, EVerbosity verbosity)
{
    return Category{name, verbosity};
}

template <typename... TArgs>
inline void Log::Verbose(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs)
{
    ost::log::internal::pLoggerInstance->PostMessage(c, EVerbosity::Verbose, std::vformat(fmtStr, std::make_format_args(fmtArgs...)));
}

template <typename... TArgs>
inline void Log::Log(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs)
{
    ost::log::internal::pLoggerInstance->PostMessage(c, EVerbosity::Message, std::vformat(fmtStr, std::make_format_args(fmtArgs...)));
}

template <typename... TArgs>
inline void Log::Warning(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs)
{
    ost::log::internal::pLoggerInstance->PostMessage(c, EVerbosity::Warning, std::vformat(fmtStr, std::make_format_args(fmtArgs...)));
}

template <typename... TArgs>
inline void Log::Error(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs)
{
    ost::log::internal::pLoggerInstance->PostMessage(c, EVerbosity::Error, std::vformat(fmtStr, std::make_format_args(fmtArgs...)));
}

template <typename... TArgs>
inline void Log::Critical(const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs)
{
    ost::log::internal::pLoggerInstance->PostMessage(c, EVerbosity::Critical, std::vformat(fmtStr, std::make_format_args(fmtArgs...)));
}

template <typename... TArgs>
inline void Log::Assert(bool condition, const Category& c, std::string_view fmtStr, TArgs&&... fmtArgs)
{
    if (condition)
    {
        return;
    }

    Critical(c, fmtStr, std::forward<TArgs>(fmtArgs)...);
    ost::internal::utility::AssertFailImpl();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------