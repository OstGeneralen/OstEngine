// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Engine.h"
#include "Game/GameModuleInternal.h"
#include <OstEngine/Configuration/CmdArg.h>

#include <OstLog/OstLogger.h>
#include <Application/Window/AppWindow.h>
#include <EngineComponentRegistration.h>
#include <EngineCmdArgs.h>

// ------------------------------------------------------------

OSTLOG_LOG_INSTANCE(EngLog);

// ------------------------------------------------------------

ost::COstEngine::COstEngine(const SAppCmdArgs& cmdArgs, CAppWindow& targetWin)
	: _moduleLoader()
	, _targetWindowPtr(&targetWin)
	, _gameInstancePtr(nullptr)
	, _inputSystem()
	, _assetsSystem()
	, _objectSystem()
{
	Engine_RegisterCoreComponents(_objectSystem.GetComponentTypeRegistry());
	_targetWindowPtr->GetInputEventProvider().BindInputSystem(_inputSystem);

	_assetsSystem.SetRootPath( cmdArgs.ReadWithDefault<std::string>(ArgAssetsPath, "Assets/"));
	EngLog.Log(OstLogLevel::Info, "Root asset path set to '{}'", _assetsSystem.MakeAssetPath("").string());

	std::string gameModuleName = "";
	if (cmdArgs.TryRead<std::string>(ArgGameModule, gameModuleName))
	{
		LoadGameModule(gameModuleName.c_str());
	}
}

// ------------------------------------------------------------

void ost::COstEngine::LoadGameModule(const char* moduleName)
{
	if (_moduleLoader.LoadModule(moduleName) == ostengine_internal::ModuleLoaderStatus_Success)
	{
		_gameInstancePtr = _moduleLoader.CreateGameModuleInstance();
		_moduleLoader.BindEngineInterface(this);
		EngLog.Log(OstLogLevel::Info, "Loaded game module '{}' and created instance", std::string(moduleName));

		_gameInstancePtr->RegisterGameComponents(_objectSystem.GetComponentTypeRegistry());
		_gameInstancePtr->OnLoad();
	}
	else
	{
		EngLog.Log(OstLogLevel::Warning, "Failed to load specified game module '{}'", std::string(moduleName));
	}
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
		EngLog.Log(OstLogLevel::Info, "Shutting down with active game module. Releasing module.");
		_gameInstancePtr->OnUnload();
		_moduleLoader.ReleaseGameModuleInstance(&_gameInstancePtr);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------