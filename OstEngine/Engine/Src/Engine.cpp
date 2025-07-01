// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Engine.h"
#include "Application/Config/ConfigFile.h"
#include "Game/GameModuleInternal.h"

#include <OstLog/OstLogger.h>


OSTLOG_LOG_INSTANCE(OstEngineLog);

// ------------------------------------------------------------

void ost::COstEngine::LoadGameModule(const char* moduleName)
{
	if (_moduleLoader.LoadModule(moduleName) == ostengine_internal::ModuleLoaderStatus_Success)
	{
		_gameInstancePtr = _moduleLoader.CreateGameModuleInstance();
		_moduleLoader.BindEngineInterface(this);
		OstEngineLog.Log(OstLogLevel::Info, "Loaded game module '{}' and created instance", std::string(moduleName));

		_gameInstancePtr->RegisterGameComponentTypes(_objectSystem.ComponentsRegistry());
		
	}
	else
	{
		OstEngineLog.Log(OstLogLevel::Warning, "Failed to load specified game module '{}'", std::string(moduleName));
	}
}

// ------------------------------------------------------------

void ost::COstEngine::InitSystem_Assets(const std::filesystem::path& assetsRootPath)
{
	_assetsSystem.SetRootPath(assetsRootPath);
}

// ------------------------------------------------------------

void ost::COstEngine::InitSystem_Rendering(CTextureRenderTarget& engineRenderTarget)
{
}

// ------------------------------------------------------------

void ost::COstEngine::InitSystem_Input(input::CInputEventProvider& eventProvider)
{
	eventProvider.BindInputSystem(_inputSystem);
}

// ------------------------------------------------------------

ost::IAssetsSystem& ost::COstEngine::GetSystem_Assets()
{
	return _assetsSystem;
}

// ------------------------------------------------------------

ost::input::IInputSystem& ost::COstEngine::GetSystem_Input()
{
	return _inputSystem;
}

// ------------------------------------------------------------

void ost::COstEngine::EngineTick()
{
}

// ------------------------------------------------------------

void ost::COstEngine::Shutdown()
{
	if (_moduleLoader.HasLoadedModule())
	{
		OstEngineLog.Log(OstLogLevel::Info, "Shutting down with active game module. Releasing module.");
		_gameInstancePtr->Shutdown();
		_moduleLoader.ReleaseGameModuleInstance(&_gameInstancePtr);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------