// OstEngine Code - Copyright (c) Kasper Esbjornsson 2022

// Note: This file is currently windows specific!

#include <Common/Public/Debugging/Logging/LoggingFunctionLibrary.h>
#include <windows.h>
#include <chrono>

std::string ost::logging::VerbosityToString(ELogVerbosity v)
{
	switch (v)
	{
	case ost::ELogVerbosity::Verbose: return std::move(std::string("VER"));
	case ost::ELogVerbosity::Log: return std::move(std::string("MSG"));
	case ost::ELogVerbosity::Confirm: return std::move(std::string("CON"));
	case ost::ELogVerbosity::Warning: return std::move(std::string("WRN"));
	case ost::ELogVerbosity::Error: return std::move(std::string("ERR"));
	}

	return "";
}

int ost::logging::GetConsoleColorCode(EConsoleColor c)
{
	switch (c)
	{
	case ost::EConsoleColor::Green: return 10;
	case ost::EConsoleColor::Cyan: return 11;
	case ost::EConsoleColor::Red: return 12;
	case ost::EConsoleColor::Magenta: return 13;
	case ost::EConsoleColor::Yellow: return 14;
	case ost::EConsoleColor::White: return 15;
	case ost::EConsoleColor::Default: return 8;
	case ost::EConsoleColor::DefaultAccent: return 7;
	}

	return 7;
}

void ost::logging::SetConsoleColor(int code)
{
	HANDLE conHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(conHandle, code);
}