#include "Game_GameModule.h"
#include "GameInstance.h"

// ------------------------------------------------------------

class GameModuleInstance : public ost::IGameModuleInstance
{
	game::CGameInstance GameInstance;

	virtual ost::IGameInstance& GetGameInstance() override
	{
		return GameInstance;
	}
};

// ------------------------------------------------------------

GAME_API ost::IGameModuleInstance* PROCNAME_MakeModuleInstance()
{
	return new GameModuleInstance();
}

// ------------------------------------------------------------

GAME_API void PROCNAME_ReleaseModuleInstance(ost::IGameModuleInstance* moduleInstance)
{
	delete moduleInstance;
}

// ------------------------------------------------------------