// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Application/Config/Configurations.h"

// ------------------------------------------------------------

namespace ost
{
	struct SEngineConfigurations : public SConfig
	{
		int32 WindowWidth = 1600;
		int32 WindowHeight = 900;
		std::string ModuleName = "";
		std::string AssetsDir = "";

		SEngineConfigurations()
		{
			Register("-w", WindowWidth);
			Register("WinWidth", WindowWidth);

			Register("-h", WindowHeight);
			Register("WinHeight", WindowHeight);

			Register("-game-module", ModuleName);
			Register("GameModule", ModuleName);

			Register("-assets-directory", AssetsDir);
		}
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------