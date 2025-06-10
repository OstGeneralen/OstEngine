// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Debug/Logging/LogMessage.h"
#include <chrono>

// ------------------------------------------------------------

ost::SLogMessage::SLogMessage(const std::string& msg, ELogLevel level)
	: Message(msg)
	, Timestamp(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now()))
	, Level(level)
{
}

// ------------------------------------------------------------

std::string ost::SLogMessage::FormatTimestamp(ETimestampFormat fmt) const
{
	auto ts = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::from_time_t(Timestamp));

	switch (fmt)
	{
	case ETimestampFormat::HH_MM_SS:
		return std::format("{:%H:%M:%S}", ts);
	}

	return "";
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
