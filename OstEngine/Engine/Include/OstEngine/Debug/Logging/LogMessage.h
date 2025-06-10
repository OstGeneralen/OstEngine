// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Debug/Logging/LogLevel.h"

#include <string>
#include <string_view>
#include <format>

// ------------------------------------------------------------

namespace ost
{
	template<typename ... TArgs>
	static std::string FormatString(std::string_view fmtStr, TArgs&& ... fmt)
	{
		return std::vformat(fmtStr, std::make_format_args(fmt...));
	}

	enum class ETimestampFormat
	{
		HH_MM_SS,
	};

	struct SLogMessage
	{
		SLogMessage(const std::string& message, ELogLevel level );
		SLogMessage(const SLogMessage&) = default;
		SLogMessage(SLogMessage&&) noexcept = default;

		std::string FormatTimestamp(ETimestampFormat fmt) const;

		std::string Message;
		uint64 Timestamp;
		ELogLevel Level;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------