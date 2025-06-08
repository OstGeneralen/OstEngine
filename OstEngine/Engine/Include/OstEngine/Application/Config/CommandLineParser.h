// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Application/Config/ConfigValues.h"
#include <vector>
#include <string>

// ------------------------------------------------------------

namespace ost
{
	struct SCommandLineValue
	{
		SCommandLineValue() = default;
		SCommandLineValue(const std::string cmdStr, const std::string valStr = "")
			: _commandName(cmdStr)
			, _commandValue(valStr)
		{
		}
		SCommandLineValue(const SCommandLineValue&) = default;
		SCommandLineValue(SCommandLineValue&&) noexcept = default;

		SCommandLineValue& operator=(const SCommandLineValue&) = default;
		SCommandLineValue& operator=(SCommandLineValue&&) noexcept = default;

		bool operator==(const std::string& s) const
		{
			return _commandName == s;
		}

		float ReadAsFloat(float defVal = 0.0f) const
		{
			try { return std::stof(_commandValue); }
			catch (std::exception e) {}
			return defVal;
		}
		int ReadAsInt( int defVal = 0 ) const
		{
			try { return std::stoi(_commandValue); }
			catch (std::exception e) {}
			return defVal;
		}
		std::string ReadAsString() const
		{
			return _commandValue;
		}

		const bool HasValue() const
		{
			return _commandValue.size() > 0;
		}

		const std::string& Name() const { return _commandName; }
		const std::string& Value() const { return _commandValue; }

	private:
		std::string _commandName;
		std::string _commandValue;
	};

	class CCommandLineParser
	{
	public:
		CCommandLineParser(char* commandLineArgs[], int numArgs);
		CCommandLineParser(const char* commandLineString);
		CCommandLineParser(const wchar_t* commandLineStringW);

		float ReadArg(const app_config::CfgFloat& commandLineArg);
		int ReadArg(const app_config::CfgInt& commandLineArg);
		std::string ReadArg(const app_config::CfgStr& commandLineArg);

		const std::vector<SCommandLineValue>& GetParsedValues() const;

	private:
		SCommandLineValue* GetCmdValue(const std::string& cmdValName);
		void ParseCommandLine(const std::string& commandLine);

		std::vector<SCommandLineValue> _values;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------