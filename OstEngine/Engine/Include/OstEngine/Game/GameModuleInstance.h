// OstEngine - Copyright(c) 2025 Kasper Esbj�rnsson (MIT License)
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