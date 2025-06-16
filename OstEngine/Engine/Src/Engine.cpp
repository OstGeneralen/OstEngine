// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "Engine.h"

#include <OstLog/OstLogger.h>

#include "Application/Config/ConfigFile.h"

#include <unordered_map>
#include <format>

// ------------------------------------------------------------

ost::COstEngine::COstEngine(SEngineInitializationOptions initOptions)
{
	GetLogger().INFO("OstEngine - Engine initialization started");
	// 1. Initialize engine config from options
	_configuration.ParseCommandLine(*initOptions.CmdLineArgs);
	// To load the config file, we want to use any potential path config from the args provided
	std::string assetDirectory = _configuration.AssetsDir;
	if (!assetDirectory.ends_with('/')) assetDirectory.append("/");
	CConfigFile configFile(assetDirectory + "EngineConfig.cfg");
	_configuration.ParseConfigFile(configFile);

	// 2. Initialize rendering
	_appWindow = _renderContext.Initialize(_configuration.WindowWidth, _configuration.WindowHeight);
	_appWindow->BindInputSystem(&_inputSystem);
	
	// 3. Load game module here

}

// ------------------------------------------------------------
int ost::COstEngine::Run()
{
	while (_appWindow->IsOpen())
	{
		_appWindow->ProcessEvents();

		_renderContext.BeginFrame();

		_renderContext.EndFrame();
	}

	GetLogger().DEBUG("OstEngine - Shutdown requested, cleaning up render context");
	_renderContext.Release(&_appWindow);
	GetLogger().INFO("OstEngine - Cleanup complete, shutting down ost engine");
	return 0;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------