// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <string>

// ------------------------------------------------------------

namespace ost
{
	namespace app_config
	{
		template<typename T>
		struct TConfigValue
		{
			TConfigValue(const std::string cmdArg, const std::string cfgName, T dv)
				: ArgName{ cmdArg }
				, CfgName{ cfgName }
				, DefaultValue{ dv }
			{
			}
			const std::string ArgName;
			const std::string CfgName;
			const T DefaultValue;
		};

		using CfgFloat = TConfigValue<float>;
		using CfgInt = TConfigValue<int>;
		using CfgStr = TConfigValue<std::string>;
	}

	namespace cfg_val
	{
		const static app_config::CfgInt cmdArg_WinWidth{ "-w", "WinWidth", 1920};
		const static app_config::CfgInt cmdArg_WinHeight{ "-h", "WinHeight", 1080};
		const static app_config::CfgStr cmdArg_GameModule("-module", "GameModule", "");
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------