// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

// ------------------------------------------------------------
// GameModuleInternal.cpp
// ------------------------------------------------------------
// Ahh so you decided to delve into this one as well?
// Well, you have been warned (see GameModuleInternal.h)
// ------------------------------------------------------------

#include "OstEngine/Game/GameModuleInternal.h"
#include "OstEngine/Game/GameModule.h"

using namespace ostengine_internal;

#define STRINGIFY(x) #x
#define STRINGIFYMACRO(x) STRINGIFY(x)

// ------------------------------------------------------------
// WIN32 Impl
// ------------------------------------------------------------
#if _WIN32
#include <Windows.h>

// ------------------------------------------------------------

ModuleLoaderStatusCode_t CGameModuleLoader::LoadModule(const char* modulePath)
{
    HMODULE moduleHandle = LoadLibraryA(modulePath);

    if (!moduleHandle)
    {
        return ModuleLoaderStatus_Failure | ModuleLoaderStatus_ModuleFailedLoad;
    }

    ModuleLoaderStatusCode_t status = ModuleLoaderStatus_Success;

    _makeModuleProc = (MakeGameModuleProc)GetProcAddress(moduleHandle, STRINGIFYMACRO(PROCNAME_MakeModuleInstance));;
    if (!_makeModuleProc)
    {
        status = status | ModuleLoaderStatus_Failure | ModuleLoaderStatus_MakeProcNotFound;
    }

    _releaseModuleProc = (ReleaseGameModuleProc)GetProcAddress(moduleHandle, STRINGIFYMACRO(PROCNAME_ReleaseModuleInstance));
    if (!_releaseModuleProc)
    {
        status = status | ModuleLoaderStatus_Failure | ModuleLoaderStatus_ReleaseProcNotFound;
    }

    if (status != ModuleLoaderStatus_Success)
    {
        _makeModuleProc = nullptr;
        _releaseModuleProc = nullptr;
        FreeLibrary(moduleHandle);
        return status;
    }

    _moduleHandle = moduleHandle;
    return ModuleLoaderStatus_Success;
}

// ------------------------------------------------------------

void ostengine_internal::CGameModuleLoader::ReleaseModule()
{
    if (HasLoadedModule())
    {
        FreeLibrary((HMODULE)_moduleHandle);
        _moduleHandle = nullptr;
        _makeModuleProc = nullptr;
        _releaseModuleProc = nullptr;
    }
}

// ------------------------------------------------------------

bool ostengine_internal::CGameModuleLoader::HasLoadedModule() const
{
    return _moduleHandle != nullptr && 
        _makeModuleProc != nullptr && 
        _releaseModuleProc != nullptr;
}

// ------------------------------------------------------------

ost::IGameModuleInstance* ostengine_internal::CGameModuleLoader::CreateGameModuleInstance()
{
    if (_makeModuleProc != nullptr && _releaseModuleProc != nullptr)
    {
        return _makeModuleProc();
    }
    return nullptr;
}

// ------------------------------------------------------------

void ostengine_internal::CGameModuleLoader::ReleaseGameModuleInstance(ost::IGameModuleInstance* instancePtr)
{
    if (instancePtr != nullptr && _makeModuleProc != nullptr && _releaseModuleProc != nullptr)
    {
        _releaseModuleProc(instancePtr);
    }
}

// ------------------------------------------------------------

#endif // _WIN32
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------