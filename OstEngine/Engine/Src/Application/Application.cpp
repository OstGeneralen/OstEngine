// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Application/Application.h"
#include "Application/Window/AppWindow.h"
#include "Application/Config/EngineConfiguration.h"
#include "Application/Config/ConfigFile.h"
#include "Engine.h"

// ------------------------------------------------------------

#include <OstLog/CoreAPI.h>
#include <OstLog/Sinks/FileLogSink.h>
#include <OstLog/Sinks/ConsoleLogSink.h>

namespace ostengine_logging
{
	ost::log::CFileLogSink* FileLogger{ nullptr };
	ost::log::CConsoleLogSink* ConsoleLogger{ nullptr };

	void InitializeLogging(std::filesystem::path logOutputDirectoryPath, const char* logPrimaryName)
	{
		FileLogger = new ost::log::CFileLogSink(logOutputDirectoryPath, logPrimaryName);
		ConsoleLogger = new ost::log::CConsoleLogSink();
		OstLogger_RegisterLogSink(*FileLogger);
		OstLogger_RegisterLogSink(*ConsoleLogger);
		OstLogger_RunLogger();
	}

	void ShutdownLogging()
	{
		OstLogger_PostShutdownSignal();
		OstLogger_AwaitShutdown();
		delete FileLogger;
		delete ConsoleLogger;
	}
}

// ------------------------------------------------------------

ost::CApplication::CApplication(const SCommandArgs& cmdArgs)
{
	// ------------------------------------------------------------
	// 1. COMMAND PARSING
	// ------------------------------------------------------------
	// 1.1: Parse the command line args
	SEngineConfigurations engineCfg{};
	engineCfg.ParseCommandLine(cmdArgs);

	// 1.2: Construct the potential config file path and parse the file into the engine config
	std::filesystem::path engCfgPath = std::filesystem::path(engineCfg.AssetsDir) / std::filesystem::path("EngineConfig.cfg");
	const CConfigFile engineCfgFile(engCfgPath);
	engineCfg.ParseConfigFile(engineCfgFile);

	// ------------------------------------------------------------
	// 2. INITIALIZE LOGGING
	// ------------------------------------------------------------
	ostengine_logging::InitializeLogging("Logs/", engineCfg.ProjectName.c_str());

	// ------------------------------------------------------------
	// 3. APP WINDOW CREATE
	// ------------------------------------------------------------
	_appWindowPtr = new CAppWindow();
	_appWindowPtr->Create(engineCfg.WindowWidth, engineCfg.WindowHeight, engineCfg.ProjectName.c_str());
	_appWindowPtr->InitGUI();

	// ------------------------------------------------------------
	// 4. ENGINE INITIALIZATION
	// ------------------------------------------------------------
	_enginePtr = new COstEngine();
	_enginePtr->InitSystem_Assets(engineCfg.AssetsDir);
	_enginePtr->InitSystem_Input(_appWindowPtr->GetInputEventProvider());
	_enginePtr->InitSystem_Rendering(_appWindowPtr->GetWindowRenderBuffer());

	// ------------------------------------------------------------
	// 5. GAME MODULE LOADING
	// ------------------------------------------------------------
	if (engineCfg.ModuleName.empty() == false)
	{
		_enginePtr->LoadGameModule(engineCfg.ModuleName.c_str());
	}
}


// ------------------------------------------------------------

ost::CApplication::~CApplication()
{
}

// ------------------------------------------------------------

void ost::CApplication::Run()
{
	while (_appWindowPtr->ShouldRemainOpen())
	{
		_appWindowPtr->PollEvents();
		_appWindowPtr->BeginWindowRenderFrame();

		_enginePtr->EngineTick();

		_appWindowPtr->EndWindowRenderFrame();
	}

	_enginePtr->Shutdown();

	delete _enginePtr;
	_appWindowPtr->Destroy();
	delete _appWindowPtr;

	ostengine_logging::ShutdownLogging();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------