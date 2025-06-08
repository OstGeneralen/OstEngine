// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Application/Config/ConfigValues.h"
#include "OstEngine/Application/Config/NamedConfigValue.h"

#include <vector>
#include <string>

// ------------------------------------------------------------

namespace ost
{
	class CCommandLineParser
	{
	public:
		CCommandLineParser(char* commandLineArgs[], int numArgs);
		CCommandLineParser(const char* commandLineString);
		CCommandLineParser(const wchar_t* commandLineStringW);

		bool ContainsArg(const app_config::CfgFloat& commandLineArg);
		bool ContainsArg(const app_config::CfgInt& commandLineArg);
		bool ContainsArg(const app_config::CfgStr& commandLineArg);

		float ReadArg(const app_config::CfgFloat& commandLineArg);
		int ReadArg(const app_config::CfgInt& commandLineArg);
		std::string ReadArg(const app_config::CfgStr& commandLineArg);

		const std::vector<SNamedConfigValue>& GetParsedValues() const;

	private:
		SNamedConfigValue* GetCmdValue(const std::string& cmdValName);
		void ParseCommandLine(const std::string& commandLine);

		std::vector<SNamedConfigValue> _values;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------