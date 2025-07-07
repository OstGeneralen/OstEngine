// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstLog/Sinks/FileLogSink.h"
#include "OstLog/MessageFormatter.h"
#include "OstLog/Logging/LoggingInstance.h"

#include <format>
#include <chrono>
#include <fstream>

namespace chr = std::chrono;

OSTLOG_LOG_INSTANCE(FileSinkLog);

// ------------------------------------------------------------

ost::log::CFileLogSink::CFileLogSink(std::filesystem::path logFileDirectory, std::string logFileMainName)
	: CLogSink(LOG_LEVELS_DETAILED)
{
	if (!std::filesystem::exists(logFileDirectory))
	{
		std::filesystem::create_directory(logFileDirectory);
	}

	const auto now = chr::system_clock::now();
	const auto days = chr::floor<chr::days>(now);
	const chr::year_month_day ymd{ days };
	const chr::hh_mm_ss hms{ now - days };

	unsigned int dayNum = (unsigned)ymd.day();
	unsigned int monthNum = (unsigned)ymd.month();
	int yearNum = (int)ymd.year();
	const std::string ymdStr = std::vformat("{}-{}-{}", std::make_format_args(dayNum, monthNum, yearNum));

	int hNum = hms.hours().count();
	int mNum = hms.minutes().count();
	int sNum = hms.seconds().count();
	const std::string hmsStr = std::vformat("{}-{}-{}", std::make_format_args(hNum, mNum, sNum));

	const std::string logFileName = std::vformat("{} {} {}.log", std::make_format_args(logFileMainName, ymdStr, hmsStr));

	_activeLogFilePath = logFileDirectory / logFileName;
	std::string outputStr = _activeLogFilePath.string();
	std::replace(outputStr.begin(), outputStr.end(), '\\', '/');
	FileSinkLog.Log(ELogLevel::Info, "File logger will write to '{}'",  outputStr);
	std::ofstream cfileStr(_activeLogFilePath); // Thank you C++ for not providing an easy std::filesystem::create_file
	cfileStr.close();
}

// ------------------------------------------------------------

void ost::log::CFileLogSink::Log(const SLogMessage& msg)
{
	const SMessageFormatter msgFmt{ msg };
	_contentStream << "[" << msgFmt.LevelStr_Full() << " | " << msg.LoggerName << "] " << "[" << msgFmt.TimeStr_HHMMSSMSMS() << "] '" << msgFmt.MessageStr() << "'\n";
	
	for (const auto& subMsg : msg.SubMessages)
	{
		const SMessageFormatter subMsgFmt{ subMsg };
		_contentStream << "--DETAIL-- " << subMsgFmt.MessageStr() << "\n";
	}

	if (_contentStream.view().length() > 4096)
	{
		Flush();
	}
}

// ------------------------------------------------------------

void ost::log::CFileLogSink::Flush()
{
	std::ofstream writeStream{ _activeLogFilePath, std::ios::ate };
	writeStream << _contentStream.view();
	writeStream.close();
	_contentStream.clear();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------