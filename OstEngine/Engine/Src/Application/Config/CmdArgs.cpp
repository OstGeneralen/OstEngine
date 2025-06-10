// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/Application/Config/CmdArgs.h>

#include <algorithm>
#include <sstream>

// ------------------------------------------------------------

ost::SCommandArgs::SCommandArgs(char* args[], int argc)
{
	std::stringstream argsStream;
	for (int i = 0; i < argc; ++i)
	{
		argsStream << args[i];
		if (i < argc - 1)
		{
			argsStream << ' ';
		}
	}

	BuildCommandArgsList(argsStream.str());
}

// ------------------------------------------------------------

ost::SCommandArgs::SCommandArgs(const char* argStr)
{
	BuildCommandArgsList(argStr);
}

// ------------------------------------------------------------

ost::SCommandArgs::SCommandArgs(const wchar_t* argStr)
{
	std::wstring asW{ argStr };
	std::string asS(asW.length(), 0);
	std::transform(asW.begin(), asW.end(), asS.begin(), [](wchar_t c) { return static_cast<char>(c); });
	BuildCommandArgsList(asS);
}

// ------------------------------------------------------------

namespace string_parse
{
	bool IsNonWordCharacter(char c)
	{
		return c == ' ' || c <= 31; // 31 is the last control character
	}

	size_t FindWordStartIndex(const std::string& inString, size_t fromOffset)
	{
		for (size_t idx = fromOffset; idx < inString.size(); ++idx)
		{
			if (!IsNonWordCharacter(inString[idx]))
			{
				return idx;
			}
		}
		return std::string::npos;
	}

	size_t FindWordEndIndex(const std::string& inString, size_t wordStartIndex)
	{
		for (size_t idx = wordStartIndex; idx < inString.size(); ++idx)
		{
			if (IsNonWordCharacter(inString[idx]))
			{
				return idx;
			}
		}
		return std::string::npos;
	}
}

// ------------------------------------------------------------

void ost::SCommandArgs::BuildCommandArgsList(const std::string& fromStr)
{
	size_t readOffset = 0;

	// Split the string into each individual substring delimited by space
	do 
	{
		const size_t nextWordStart = string_parse::FindWordStartIndex(fromStr, readOffset);
		const size_t nextWordEnd = string_parse::FindWordEndIndex(fromStr, nextWordStart);
		readOffset = nextWordEnd;

		if (nextWordStart != std::string::npos && nextWordEnd != std::string::npos)
		{
			_splitCommandLine.emplace_back(fromStr.substr(nextWordStart, nextWordEnd - nextWordStart));
		}
	} while (readOffset < fromStr.length() && readOffset != std::string::npos);
}

// ------------------------------------------------------------

void ost::SCommandArgs::ForeachCommand(ost::SCommandArgs::ArgsIT_f f) const
{
	for (size_t idx = 0; idx < _splitCommandLine.size(); ++idx)
	{
		if (_splitCommandLine[idx].GetType() == ECommandArgType::Command)
		{
			if (_splitCommandLine[idx + 1].GetType() == ECommandArgType::Value)
			{
				f(_splitCommandLine[idx].GetString(), _splitCommandLine[idx + 1].GetString());
				++idx;
			}
			else
			{
				f(_splitCommandLine[idx].GetString(), "");
			}
		}
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------