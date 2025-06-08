#include "OstEngine/Application/Config/ConfigFileParser.h"

#include <filesystem>
#include <fstream>
#include <sstream>

// Expected format:
// Name= value
// Name= value

// ------------------------------------------------------------

namespace ascii
{
	bool IsCharInRange(char v, char min, char max)
	{
		return min <= v && v <= max;
	}

	bool IsBlankOrControlChar(char c)
	{
		constexpr static char ascii_ctrl_start = 0;
		constexpr static char ascii_ctrl_end = 31;

		return c == ' ' || IsCharInRange(c, ascii_ctrl_start, ascii_ctrl_end);
	}

	size_t FirstNotBlankOrControlChar(const std::string& str, size_t offset)
	{
		for (size_t idx = offset; idx < str.size(); ++idx)
		{
			if (!IsBlankOrControlChar(str[idx]))
			{
				return idx;
			}
		}
		return std::string::npos;
	}

	size_t LastNotBlankOrControlCharInWord(const std::string& str, size_t offset)
	{
		for (size_t idx = offset; idx < str.size(); ++idx)
		{
			if (IsBlankOrControlChar(str[idx]))
			{
				return idx - 1;
			}
		}
		return std::string::npos;
	}
}

// ------------------------------------------------------------


void ost::CConfigFileParser::ReadConfigFile(const std::string cfgPath)
{
	if (!std::filesystem::exists(cfgPath))
	{
		return;
	}

	std::ifstream fileStream(cfgPath, std::ios::beg | std::ios::binary);
	std::stringstream cfgStringStream;
	cfgStringStream << fileStream.rdbuf();
	fileStream.close();

	std::string configContentStr = cfgStringStream.str();
	size_t readOffset = 0;

	// Read the file contents and parse into config values
	do
	{
		const size_t nameStartIdx = ascii::FirstNotBlankOrControlChar(configContentStr, readOffset);
		const size_t nameEndIdx = ascii::LastNotBlankOrControlCharInWord(configContentStr, nameStartIdx);
		const size_t nextAssignSymbolIdx = configContentStr.find_first_of('=', readOffset);
		const size_t nextNewLine = configContentStr.find_first_of('\n', readOffset);

		if (nextAssignSymbolIdx >= nextNewLine) // There just isn't a value assigned here so skip
		{
			readOffset = nextNewLine + 1;
			continue;
		}

		const size_t valueStartIdx = ascii::FirstNotBlankOrControlChar(configContentStr, nextAssignSymbolIdx + 1);
		const size_t valueEndIdx = ascii::LastNotBlankOrControlCharInWord(configContentStr, valueStartIdx);

		_values.emplace_back(
			configContentStr.substr(nameStartIdx, (nameEndIdx - nameStartIdx) + 1),
			configContentStr.substr(valueStartIdx, (valueEndIdx - valueStartIdx) + 1)
		);

		readOffset = nextNewLine != std::string::npos ? nextNewLine + 1 : nextNewLine;
	} while (readOffset != std::string::npos);
}

// ------------------------------------------------------------

void ost::CConfigFileParser::WriteConfigFile(const std::string cfgPath)
{
	std::ofstream writeStream(cfgPath, std::ios::trunc);
	for (size_t i = 0; i < _values.size(); ++i)
	{
		writeStream << _values[i].Name() << " = " << _values[i].Value();
		if (i < _values.size() - 1)
		{
			writeStream << std::endl;
		}
	}
	writeStream.close();
}

// ------------------------------------------------------------

bool ost::CConfigFileParser::ContainsConfig(const app_config::CfgInt& cfgVal)
{
	return GetConfigValue(cfgVal.CfgName) != nullptr;
}

// ------------------------------------------------------------

bool ost::CConfigFileParser::ContainsConfig(const app_config::CfgFloat& cfgVal)
{
	return GetConfigValue(cfgVal.CfgName) != nullptr;
}

// ------------------------------------------------------------

bool ost::CConfigFileParser::ContainsConfig(const app_config::CfgStr& cfgVal)
{
	return GetConfigValue(cfgVal.CfgName) != nullptr;
}

// ------------------------------------------------------------

int ost::CConfigFileParser::ReadValue(const app_config::CfgInt& cfgVal, bool addAsKnown)
{
	int value = cfgVal.DefaultValue;
	SNamedConfigValue* const valPtr = GetConfigValue(cfgVal.CfgName);
	if (valPtr != nullptr)
	{
		value = valPtr->ReadAsInt(cfgVal.DefaultValue);
	}
	if (addAsKnown)
	{
		SetConfigValue(cfgVal, value);
	}

	return value;
}

// ------------------------------------------------------------

float ost::CConfigFileParser::ReadValue(const app_config::CfgFloat& cfgVal, bool addAsKnown)
{
	float value = cfgVal.DefaultValue;
	SNamedConfigValue* const valPtr = GetConfigValue(cfgVal.CfgName);
	if (valPtr != nullptr)
	{
		value = valPtr->ReadAsFloat(cfgVal.DefaultValue);
	}
	if (addAsKnown)
	{
		SetConfigValue(cfgVal, value);
	}

	return value;
}

// ------------------------------------------------------------

std::string ost::CConfigFileParser::ReadValue(const app_config::CfgStr& cfgVal, bool addAsKnown)
{
	std::string value = cfgVal.DefaultValue;
	SNamedConfigValue* const valPtr = GetConfigValue(cfgVal.CfgName);
	if (valPtr != nullptr)
	{
		value = valPtr->ReadAsString();
	}
	if (addAsKnown)
	{
		SetConfigValue(cfgVal, value);
	}

	return value;
}

// ------------------------------------------------------------

void ost::CConfigFileParser::SetConfigValue(const app_config::CfgInt& cfgVal, int value)
{
	SNamedConfigValue asNCV{ cfgVal.CfgName, std::to_string(value)};
	if (SNamedConfigValue* vPtr = GetConfigValue(cfgVal.CfgName))
	{
		(*vPtr) = asNCV;
	}
	else
	{
		_values.push_back(asNCV);
	}
}

// ------------------------------------------------------------

void ost::CConfigFileParser::SetConfigValue(const app_config::CfgFloat& cfgVal, float value)
{
	SNamedConfigValue asNCV{ cfgVal.CfgName, std::to_string(value) };
	if (SNamedConfigValue* vPtr = GetConfigValue(cfgVal.CfgName))
	{
		(*vPtr) = asNCV;
	}
	else
	{
		_values.push_back(asNCV);
	}
}

// ------------------------------------------------------------

void ost::CConfigFileParser::SetConfigValue(const app_config::CfgStr& cfgVal, const std::string& value)
{
	SNamedConfigValue asNCV{ cfgVal.CfgName, value };
	if (SNamedConfigValue* vPtr = GetConfigValue(cfgVal.CfgName))
	{
		(*vPtr) = asNCV;
	}
	else
	{
		_values.push_back(asNCV);
	}
}

// ------------------------------------------------------------

ost::SNamedConfigValue* ost::CConfigFileParser::GetConfigValue(const std::string& valueName)
{
	for (auto& val : _values)
	{
		if (val == valueName)
		{
			return &val;
		}
	}
	
	return nullptr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------