// OstEngine Code - Copyright (c) Kasper Esbjornsson 2022

#include "Common/Public/Debugging/Logging/DefaultLogger.h"
#include "Common/Public/Debugging/Timing/TimeFunctionLibrary.h"
#include <iostream>
#include <iomanip>

using namespace ost;

namespace
{
	EConsoleColor VerbosityToColor(ELogVerbosity v)
	{
		switch (v)
		{
		case ost::ELogVerbosity::Verbose: return EConsoleColor::Cyan;
		case ost::ELogVerbosity::Log: return EConsoleColor::White;
		case ost::ELogVerbosity::Confirm: return EConsoleColor::Green;
		case ost::ELogVerbosity::Warning: return EConsoleColor::Yellow;
		case ost::ELogVerbosity::Error: return EConsoleColor::Red;
		}
		return EConsoleColor::Default;
	}

	const int metaCol = logging::GetConsoleColorCode(EConsoleColor::Default);
	const int metaAccentCol = logging::GetConsoleColorCode(EConsoleColor::DefaultAccent);

	void InfoPrint(const std::string& infoText, char separator = ' ', int alignSize = 0, char fill = ' ')
	{
		char startSeparator = '[';
		char endSeparator = ']';

		if (separator == '(')
		{
			startSeparator = '(';
			endSeparator = ')';
		}
		else if (separator == '|')
		{
			startSeparator = '|';
			endSeparator = '|';
		}
		
	
		if (separator != ' ')
		{
			logging::SetConsoleColor(::metaAccentCol);
			std::cout << "[";
		}

		logging::SetConsoleColor(::metaCol);
		std::cout << std::left << std::setw(alignSize) << std::setfill(fill) << infoText;

		if (separator != ' ')
		{
			logging::SetConsoleColor(::metaAccentCol);
			std::cout << "]";
		}
	}

}


void CDefaultLogger::LogString(ELogVerbosity verbosity, std::string msg)
{
	
	const int verbosityColor = logging::GetConsoleColorCode(::VerbosityToColor(verbosity));
	
	logging::SetConsoleColor(::metaCol);
	std::cout << debugtime::GetNowAsFormattedString(false) << " ";
	std::cout << std::right << std::setw(23) << std::setfill('-') << GetInstanceName() << ": ";
	logging::SetConsoleColor(verbosityColor);
	std::cout << stringhelpers::FormatString("{}: {} ", logging::VerbosityToString(verbosity), msg) << "\n";
	
}

void ost::CDefaultLogger::PrintInfo(const std::string& infoText)
{
	
}
