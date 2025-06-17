// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstLog/MessageFormatter.h"
#include <format>

// ------------------------------------------------------------

ost::log::SMessageFormatter::SMessageFormatter(const SLogMessage& msg)
	: _msg(msg)
{
}

// ------------------------------------------------------------

std::string ost::log::SMessageFormatter::LevelStr_Full() const
{
	switch (_msg.Level)
	{
	case ELogLevel::Trace:		return "TRACE";
	case ELogLevel::Debug:		return "DEBUG";
	case ELogLevel::Info:		return "INFO";
	case ELogLevel::Warning:	return "WARNING";
	case ELogLevel::Error:		return "ERROR";
	case ELogLevel::Fatal:		return "FATAL";
	}
	return "";
}

// ------------------------------------------------------------

std::string ost::log::SMessageFormatter::LevelStr_Abbr() const
{
	switch (_msg.Level)
	{
	case ELogLevel::Trace:		return "TRC";
	case ELogLevel::Debug:		return "DBG";
	case ELogLevel::Info:		return "INF";
	case ELogLevel::Warning:	return "WRN";
	case ELogLevel::Error:		return "ERR";
	case ELogLevel::Fatal:		return "FAT";
	}
	return "";
}

// ------------------------------------------------------------

std::string ost::log::SMessageFormatter::TimeStr_HHMMSS() const
{
	auto days = std::chrono::floor<std::chrono::days>(_msg.Timestamp);
	std::chrono::hh_mm_ss hms{ _msg.Timestamp - days };

	const int h = hms.hours().count();
	const std::string hPrf = h <= 9 ? "0" : "";
	
	const int m = hms.minutes().count();
	const std::string mPrf = m <= 9 ? "0" : "";

	const int s = hms.seconds().count();
	const std::string sPrf = s <= 9 ? "0" : "";

	return std::vformat("{}{}:{}{}:{}{}", std::make_format_args(hPrf,h, mPrf, m, sPrf, s));
}

// ------------------------------------------------------------

std::string ost::log::SMessageFormatter::TimeStr_HHMMSSMSMS() const
{
	auto days = std::chrono::floor<std::chrono::days>(_msg.Timestamp);
	std::chrono::hh_mm_ss hms{ _msg.Timestamp - days };

	const int h = hms.hours().count();
	const std::string hPrf = h <= 9 ? "0" : "";

	const int m = hms.minutes().count();
	const std::string mPrf = m <= 9 ? "0" : "";

	const int s = hms.seconds().count();
	const std::string sPrf = s <= 9 ? "0" : "";

	const int ms = std::chrono::duration_cast<std::chrono::milliseconds>(hms.subseconds()).count();
	const std::string msPrf = ms <= 999 ? (ms <= 99 ? (ms <= 9 ? "000" : "00") : "0") : ""; // This ain't nice :D

	return std::vformat("{}{}:{}{}:{}{}:{}{}", std::make_format_args(hPrf, h, mPrf, m, sPrf, s, msPrf, ms));
}

// ------------------------------------------------------------

std::string ost::log::SMessageFormatter::MessageStr() const
{
	return _msg.MessageFormatter();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------