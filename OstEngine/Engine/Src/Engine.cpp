// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "Engine.h"

#include "OstEngine/Debug/Logging/LoggingContext.h"
#include "OstEngine/Debug/Logging.h"

#include <unordered_map>
#include <format>

// ------------------------------------------------------------

struct EngineConfig
{
	std::string ExePath;
	std::string GameModuleName;
	std::string WorkingPath;
	int WindowWidth = 1920;
	int WindowHeight = 1080;
};

// ------------------------------------------------------------

ost::COstEngine::COstEngine(SEngineInitializationOptions initOptions)
{
	CLoggingContext::Create();
	if (initOptions.InitLogger != nullptr)
	{
		CLoggingContext::Get()->BindLogger(initOptions.InitLogger);
	}

	// 1. Parse command line args
	EngineConfig cfg = {};
	auto cmdIt = [&cfg](const std::string& n, const std::string& v)
		{
			if (v.size() == 0) cfg.ExePath = n;
			if (n == "-w") cfg.WindowWidth = std::stoi(v);
			if (n == "-h") cfg.WindowHeight = std::stoi(v);
			if (n == "-assetPath") cfg.WorkingPath = v;
		};

	initOptions.CmdLineArgs->ForeachCommand(cmdIt);

	LOG_CONFIRM("OstEngine init");
	LOG_BEGIN_SCOPE();
	{
		LOG_INFO("Execution Path: {}", cfg.ExePath);
		LOG_INFO("Window dimensions: {}x{}", cfg.WindowWidth, cfg.WindowHeight);
		LOG_INFO("Asset Directory: {}", cfg.WorkingPath);
		LOG_INFO("Game Module: {}", cfg.GameModuleName);
	}
	LOG_END_SCOPE();

	// 2. Initialize rendering
	_appWindow = _renderContext.Initialize(cfg.WindowWidth, cfg.WindowHeight);
	
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

	LOG_INFO("Shutdown requested, cleaning up render context");
	_renderContext.Release(&_appWindow);
	LOG_INFO("Cleanup complete, shutting down ost engine");
	return 0;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------