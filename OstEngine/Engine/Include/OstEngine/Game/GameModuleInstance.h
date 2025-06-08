// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

// ------------------------------------------------------------
#include "OstEngine/Game/GameInstance.h"

namespace ost
{
	class IGameModuleInstance
	{
	public:
		virtual ~IGameModuleInstance() = default;
		virtual IGameInstance& GetGameInstance() = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------