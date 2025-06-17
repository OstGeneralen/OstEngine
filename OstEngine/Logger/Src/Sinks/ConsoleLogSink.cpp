// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstLog/Sinks/ConsoleLogSink.h"
#include "OstLog/MessageFormatter.h"

#include <iostream>
#include <iomanip>
#include <unordered_map>

// ------------------------------------------------------------

#if WIN32
#include <Windows.h>
namespace
{
	constexpr static int DarkGrey = 8;
	constexpr static int LightGrey = 7;
	constexpr static int White = 15;
	constexpr static int Green = 10;
	constexpr static int Cyan = 11;
	constexpr static int Red = 12;
	constexpr static int Yellow = 14;
	constexpr static int Purple = 13;

	const std::unordered_map<ost::log::ELogLevel, int> LevelColors = {
		{ost::log::ELogLevel::Trace, LightGrey},
		{ost::log::ELogLevel::Debug, Cyan},
		{ost::log::ELogLevel::Info, Green},
		{ost::log::ELogLevel::Warning, Yellow},
		{ost::log::ELogLevel::Error, Red},
		{ost::log::ELogLevel::Fatal, Purple},
	};

	void SetOutputCol(int c)
	{
		HANDLE cHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(cHandle, c);
	}
}
#endif

// ------------------------------------------------------------

ost::log::CConsoleLogSink::CConsoleLogSink(ELogLevel levels)
	: CLogSink(levels)
{
}

// ------------------------------------------------------------

void ost::log::CConsoleLogSink::Log(const SLogMessage& msg)
{
	const int detailColor = ::DarkGrey;

	const int timeW = 9;
	const int levelW = 4;
	const int messageOffset = timeW + levelW + 2;

	const SMessageFormatter msgFmt{ msg };
	::SetOutputCol(detailColor);
	std::cout << std::setw(timeW) << std::left << msgFmt.TimeStr_HHMMSS();
	::SetOutputCol(::LevelColors.at(msg.Level));
	std::cout << std::setw(levelW) << std::left << msgFmt.LevelStr_Abbr();
	::SetOutputCol(detailColor);
	std::cout << msg.LoggerName << ": ";
	::SetOutputCol(::White);
	 std::cout << msgFmt.MessageStr() << std::endl;

	for (const auto& subMsg : msg.SubMessages)
	{
		const SMessageFormatter subMsgFmt{ subMsg };
		::SetOutputCol(detailColor);
		std::cout << std::setw(messageOffset) << std::right << ">";
		::SetOutputCol(::LightGrey);
		std::cout << " " << subMsgFmt.MessageStr() << std::endl;
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------