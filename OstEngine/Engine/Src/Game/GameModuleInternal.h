// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

// ------------------------------------------------------------
// GameModuleInternal.h
// ------------------------------------------------------------
// No, I will not have a long ramble at the start of every 
// single file but...
// If you find yourself in this header there are two options:
//
// 1. You are very lost in the headers and should go back
// to where you came from
// 
// 2. You actually have an issue that is related to the module
// dll loading at which point I'M SO SORRY
// 
// Feel free to have a poke around. Change some things. 
// Have a good time!
// 
// BUT DON'T COME CRYING IF THE ENGINE DOESN'T BEHAVE AFTERWARDS
// kthxbyte <3
// ------------------------------------------------------------

#pragma once
#include "OstEngine/Game/GameInstance.h"

namespace ostengine_internal
{
	using ModuleLoaderStatusCode_t = unsigned int;
	inline constexpr ModuleLoaderStatusCode_t ModuleLoaderStatus_Success = 0x00000000u;
	inline constexpr ModuleLoaderStatusCode_t ModuleLoaderStatus_Failure = 0xF0000000u;
	inline constexpr ModuleLoaderStatusCode_t ModuleLoaderStatus_ModuleFailedLoad = ModuleLoaderStatus_Failure | 0x0000000Fu;
	inline constexpr ModuleLoaderStatusCode_t ModuleLoaderStatus_MakeProcNotFound = ModuleLoaderStatus_Failure | 0x000000F0u;
	inline constexpr ModuleLoaderStatusCode_t ModuleLoaderStatus_ReleaseProcNotFound = ModuleLoaderStatus_Failure | 0x00000F00u;

	class CGameModuleLoader
	{
		using MakeGameModuleProc = ost::IGameInstance* (*)();
		using ReleaseGameModuleProc = void (*)(ost::IGameInstance*);
	public:
		ModuleLoaderStatusCode_t LoadModule(const char* modulePath);
		void ReleaseModule();

		bool HasLoadedModule() const;

		ost::IGameInstance* CreateGameModuleInstance();
		void ReleaseGameModuleInstance(ost::IGameInstance** ppInstance);
	private:
		void* _moduleHandle;
		MakeGameModuleProc _makeModuleProc;
		ReleaseGameModuleProc _releaseModuleProc;
	};
}