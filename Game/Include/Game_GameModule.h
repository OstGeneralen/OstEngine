#pragma once
#include <OstEngine/Game/GameModuleInstance.h>
#include <OstEngine/Game/GameModule.h>

// ------------------------------------------------------------

#if GAME_DLL_BUILD
#define GAME_API __declspec(dllexport)
#else
#define GAME_API __declspec(dllimport)
#endif

// ------------------------------------------------------------

extern "C" GAME_API ost::IGameModuleInstance* PROCNAME_MakeModuleInstance();
extern "C" GAME_API void PROCNAME_ReleaseModuleInstance(ost::IGameModuleInstance* moduleInstance);

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------