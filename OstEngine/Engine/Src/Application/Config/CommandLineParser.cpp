// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "OstEngine/Application/Config/CommandLineParser.h"

#include <sstream>
#include <algorithm>

// ------------------------------------------------------------

ost::CCommandLineParser::CCommandLineParser(char* commandLineArgs[], int numArgs)
{
	std::stringstream commandLineStream;
	for (int i = 0; i < numArgs; ++i)
	{
		commandLineStream << commandLineArgs[i];
		if (i < numArgs - 1)
		{
			commandLineStream << " ";
		}
	}

	ParseCommandLine(commandLineStream.str());
}

// ------------------------------------------------------------

ost::CCommandLineParser::CCommandLineParser(const char* commandLineString)
{
	ParseCommandLine(commandLineString);
}

// ------------------------------------------------------------

ost::CCommandLineParser::CCommandLineParser(const wchar_t* commandLineStringW)
{
	std::wstring asWStr(commandLineStringW);
	std::string asStr(asWStr.length(), 0 );
	std::transform(asWStr.begin(), asWStr.end(), asStr.begin(), [](wchar_t wc) { return static_cast<char>(wc); });
	ParseCommandLine(asStr);
}

// ------------------------------------------------------------

bool ost::CCommandLineParser::ContainsArg(const app_config::CfgFloat& commandLineArg)
{
	return GetCmdValue(commandLineArg.ArgName) != nullptr;
}

// ------------------------------------------------------------

bool ost::CCommandLineParser::ContainsArg(const app_config::CfgInt& commandLineArg)
{
	return GetCmdValue(commandLineArg.ArgName) != nullptr;
}

// ------------------------------------------------------------

bool ost::CCommandLineParser::ContainsArg(const app_config::CfgStr& commandLineArg)
{
	return GetCmdValue(commandLineArg.ArgName) != nullptr;
}

// ------------------------------------------------------------

float ost::CCommandLineParser::ReadArg(const app_config::CfgFloat& commandLineArg)
{
	SNamedConfigValue* const cmdVal = GetCmdValue(commandLineArg.ArgName);
	if (cmdVal && cmdVal->HasValue())
	{
		return cmdVal->ReadAsFloat(commandLineArg.DefaultValue);
	}
	return commandLineArg.DefaultValue;
}

// ------------------------------------------------------------

int ost::CCommandLineParser::ReadArg(const app_config::CfgInt& commandLineArg)
{
	SNamedConfigValue* const cmdVal = GetCmdValue(commandLineArg.ArgName);
	if (cmdVal && cmdVal->HasValue())
	{
		return cmdVal->ReadAsInt(commandLineArg.DefaultValue);
	}
	return commandLineArg.DefaultValue;
}

// ------------------------------------------------------------

std::string ost::CCommandLineParser::ReadArg(const app_config::CfgStr& commandLineArg)
{
	SNamedConfigValue* const cmdVal = GetCmdValue(commandLineArg.ArgName);
	if (cmdVal && cmdVal->HasValue())
	{
		return cmdVal->ReadAsString();
	}
	return commandLineArg.DefaultValue;
}

// ------------------------------------------------------------

const std::vector<ost::SNamedConfigValue>& ost::CCommandLineParser::GetParsedValues() const
{
	return _values;
}

// ------------------------------------------------------------

ost::SNamedConfigValue* ost::CCommandLineParser::GetCmdValue(const std::string& cmdValName)
{
	for (auto& cmdVal : _values)
	{
		if (cmdVal == cmdValName)
		{
			return &cmdVal;
		}
	}

	return nullptr;
}

// ------------------------------------------------------------

void ost::CCommandLineParser::ParseCommandLine(const std::string& commandLine)
{
	// Split command line string by spaces
	size_t currentOffset = 0;
	std::vector<std::string> cmdLineSubstrings;

	size_t nextBlankSpacePosition = 0;
	do
	{
		nextBlankSpacePosition = commandLine.find_first_of(' ', currentOffset);
		cmdLineSubstrings.push_back(commandLine.substr(currentOffset, nextBlankSpacePosition - currentOffset));

		currentOffset = nextBlankSpacePosition + 1;
	} while (nextBlankSpacePosition != std::string::npos);

	std::string commandNameStr;

	for (size_t cmdIdx = 0; cmdIdx < cmdLineSubstrings.size(); ++cmdIdx)
	{
		const bool isCommandName = cmdLineSubstrings[cmdIdx].starts_with('-');
		const bool isValue = !isCommandName;

		if (commandNameStr.size() > 0 && isValue)
		{
			_values.emplace_back(commandNameStr, cmdLineSubstrings[cmdIdx]);
			commandNameStr.clear();
		}
		else if (commandNameStr.size() > 0)
		{
			_values.emplace_back(commandNameStr);
			commandNameStr.clear();
		}

		if (isCommandName)
		{
			commandNameStr = cmdLineSubstrings[cmdIdx];
		}
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------