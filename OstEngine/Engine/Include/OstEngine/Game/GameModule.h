// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

// ------------------------------------------------------------
// GameModule.h
// ------------------------------------------------------------
// To create a game project which outputs a module dll that 
// OstEngine can load:
// 
// 1. Make GameInstance type (derived from ost::IGameInstance)
// This is the full type of your game and how the engine will
// interact with you.
// 
// 2. Make a .cpp (no matching header required)
// - Include your Game Instance header
// - Define your 'API macro' as either import or export
//		import if [GAME_NAME]_BUILD_DLL is defined
//		export otherwise
// - OST_ENGINE_GAME_MODULE([API macro], [GameInstanceType])
//		in this .cpp file. Nothing else required.
// 
// Following these steps the game module should now be able to
// be loaded by either the Editor or Player depending on your
// configuration.
// ------------------------------------------------------------
#pragma once

#include "OstEngine/Game/GameInstance.h"
#include "OstEngine/Game/OstEngineGameCore.h"

#define PROCNAME_MakeModuleInstance		MakeModuleInstance
#define PROCNAME_ReleaseModuleInstance	ReleaseModuleInstance
#define PROCNAME_BindGlobalEngine		BindEngineInterface

#define OST_ENGINE_GAME_MODULE(API, GameInstanceType)		extern "C" API ost::IGameInstance* PROCNAME_MakeModuleInstance() { return new GameInstanceType(); } \
															extern "C" API void PROCNAME_ReleaseModuleInstance( ost::IGameInstance* pInstance ) { GameInstanceType* ip = (GameInstanceType*)(pInstance); delete ip; } \
															ost::IOstEngine* ost::EnginePtr = nullptr; \
															extern "C" API void PROCNAME_BindGlobalEngine( ost::IOstEngine* pEngine ) { ost::EnginePtr = pEngine; } \

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------