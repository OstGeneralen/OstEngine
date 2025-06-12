// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Application/Config/ConfigFile.h"

#include <fstream>
#include <sstream>

// ------------------------------------------------------------

namespace str_parse
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

ost::CConfigFile::CConfigFile(const std::filesystem::path& path)
{
	if (!std::filesystem::exists(path)) return;

	std::ifstream readStream(path, std::ios::binary);
	std::stringstream cfgSStream;
	cfgSStream << readStream.rdbuf();
	readStream.close();

	const std::string cfgContent = cfgSStream.str();
	size_t readIdx = 0;
	do
	{
		const size_t newLineIdx = cfgContent.find_first_of('\n', readIdx);
		const size_t lineLen = newLineIdx != std::string::npos ? newLineIdx - readIdx : std::string::npos;

		const std::string line = cfgContent.substr(readIdx, lineLen);
		Parse(line);

		readIdx = lineLen == std::string::npos ? lineLen : readIdx + lineLen + 1;
	} while (readIdx < cfgContent.length());

}

// ------------------------------------------------------------

void ost::CConfigFile::ForeachConfigValue(std::function<void(const std::string&, const std::string&)> itF) const
{
	for (auto& v : _nvPairs)
	{
		itF(v.Name, v.ValueStr);
	}
}

// ------------------------------------------------------------

void ost::CConfigFile::Parse(const std::string& line)
{
	const size_t nameStart = str_parse::FindWordStartIndex(line, 0);
	const size_t nameEnd = str_parse::FindWordEndIndex(line, nameStart);
	const size_t nameLen = nameEnd != std::string::npos ? nameEnd - nameStart : std::string::npos;

	if (nameStart == std::string::npos) return; // This contains no text, only esc seqs

	if (line[nameStart] == '[') return; // This indicates a category

	const std::string name = line.substr(nameStart, nameLen);

	if (nameEnd >= line.length())
	{
		_nvPairs.push_back({ name, "" });
		return;
	}

	const size_t idxOfAssign = line.find_first_of('=', nameEnd);
	if (idxOfAssign == std::string::npos)
	{
		_nvPairs.push_back({ name, "" });
		return;
	}

	const size_t valueStart = str_parse::FindWordStartIndex(line, idxOfAssign + 1);
	const size_t valueEnd = str_parse::FindWordEndIndex(line, valueStart);
	const size_t valueLen = valueEnd != std::string::npos ? valueEnd - valueStart : std::string::npos;

	_nvPairs.push_back({ name, line.substr(valueStart, valueLen) });
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------