// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Engine.h"
#include "Application/Config/ConfigFile.h"
#include "Game/GameModuleInternal.h"

#include <OstEngine/Game/Core/TransformComponent.h>

#include <OstLog/OstLogger.h>



OSTLOG_LOG_INSTANCE(OstEngineLog);

// ------------------------------------------------------------

ost::COstEngine::COstEngine()
{
	CComponentTypeRegistry& registry = _objectSystem.GetComponentTypeRegistry();

	// Register engine components
	registry.Register<CTransformComponent>();
}

// ------------------------------------------------------------

void ost::COstEngine::LoadGameModule(const char* moduleName)
{
	if (_moduleLoader.LoadModule(moduleName) == ostengine_internal::ModuleLoaderStatus_Success)
	{
		_gameInstancePtr = _moduleLoader.CreateGameModuleInstance();
		_moduleLoader.BindEngineInterface(this);
		OstEngineLog.Log(OstLogLevel::Info, "Loaded game module '{}' and created instance", std::string(moduleName));

		_gameInstancePtr->RegisterGameComponents(_objectSystem.GetComponentTypeRegistry());
		_gameInstancePtr->OnLoad();
		
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

ost::TPtr<ost::CScene> ost::COstEngine::NewScene(bool makeActive)
{
	return _objectSystem.CreateScene(makeActive);
}

// ------------------------------------------------------------

void ost::COstEngine::SetActiveScene(TPtr<CScene> scene)
{
	_objectSystem.SetActiveScene(scene);
}

// ------------------------------------------------------------

void ost::COstEngine::EngineTick()
{
	_objectSystem.TickActiveScene();
}

// ------------------------------------------------------------

void ost::COstEngine::Shutdown()
{
	if (_moduleLoader.HasLoadedModule())
	{
		OstEngineLog.Log(OstLogLevel::Info, "Shutting down with active game module. Releasing module.");
		_gameInstancePtr->OnUnload();
		_moduleLoader.ReleaseGameModuleInstance(&_gameInstancePtr);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------