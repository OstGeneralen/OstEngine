#pragma once
#include <OstEngine/Game/GameInstance.h>

// ------------------------------------------------------------

namespace game
{
	// This is your game class which the majority of all engine interaction will take place through
	class CGameInstance : public ost::IGameInstance
	{
		void Run() override;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
