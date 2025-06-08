// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

#include "OstEngine/Application/Config/NamedConfigValue.h"
#include "OstEngine/Application/Config/ConfigValues.h"

#include <string>
#include <vector>

// ------------------------------------------------------------


namespace ost
{
	class CConfigFileParser
	{
	public:
		void ReadConfigFile(const std::string cfgPath);
		void WriteConfigFile(const std::string cfgPath);

		bool ContainsConfig(const app_config::CfgInt& cfgVal);
		bool ContainsConfig(const app_config::CfgFloat& cfgVal);
		bool ContainsConfig(const app_config::CfgStr& cfgVal);

		int ReadValue(const app_config::CfgInt& cfgVal, bool addAsKnown = true);
		float ReadValue(const app_config::CfgFloat& cfgVal, bool addAsKnown = true);
		std::string ReadValue(const app_config::CfgStr& cfgVal, bool addAsKnown = true);

		void SetConfigValue(const app_config::CfgInt& cfgVal, int value);
		void SetConfigValue(const app_config::CfgFloat& cfgVal, float value);
		void SetConfigValue(const app_config::CfgStr& cfgVal, const std::string& value);
	private:
		SNamedConfigValue* GetConfigValue(const std::string& valueName);

		std::vector<SNamedConfigValue> _values;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------