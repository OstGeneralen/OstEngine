#include <OstEngine/Game/GameModule.h>
#include "GameInstance.h"

#if GAME_DLL_BUILD
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif

OST_ENGINE_GAME_MODULE( GAME_API, game::CGameInstance )