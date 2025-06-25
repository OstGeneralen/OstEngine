// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		enum class ELogLevel
		{
			NONE	= 0,
			Trace	= 1 << 0,		// Very verbose diagnostics and debug info
			Debug	= 1 << 1,		// Detailed diagnostics and debug info
			Info	= 1 << 2,		// Normal behaviour and milestones (I.e confirmation of initialization, state changes etc.)
			Warning = 1 << 3,		// Potential future errors and data mismatches
			Error	= 1 << 4,		// Actionable errors that can be recovered from but should be considered
			Fatal	= 1 << 5,		// Fatal errors that will cause exceptions or execution ending problems
		};
	}
}

static constexpr ost::log::ELogLevel operator|(ost::log::ELogLevel a, ost::log::ELogLevel b)
{
	return static_cast<ost::log::ELogLevel>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
}

static constexpr ost::log::ELogLevel operator&(ost::log::ELogLevel a, ost::log::ELogLevel b)
{
	return static_cast<ost::log::ELogLevel>(static_cast<unsigned>(a) & static_cast<unsigned>(b));
}

static constexpr ost::log::ELogLevel operator~(ost::log::ELogLevel a)
{
	return static_cast<ost::log::ELogLevel>(~static_cast<unsigned>(a));
}

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		constexpr static ELogLevel LOG_LEVELS_ERRORS_ONLY = ELogLevel::Error | ELogLevel::Fatal;
		constexpr static ELogLevel LOG_LEVELS_LIMITED = ELogLevel::Warning | LOG_LEVELS_ERRORS_ONLY;
		constexpr static ELogLevel LOG_LEVELS_DEFAULT = ELogLevel::Info | LOG_LEVELS_LIMITED;
		constexpr static ELogLevel LOG_LEVELS_DETAILED = ELogLevel::Debug | ELogLevel::Trace | LOG_LEVELS_DEFAULT;
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------