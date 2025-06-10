// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "Engine.h"
#include "Application/AppRuntimeStatics.h"

#include "OstEngine/Debug/Logging/LoggingContext.h"
#include "Debug/Logging/LoggerIOStream.h"
#include "OstEngine/Debug/Logging.h"

#include <unordered_map>
#include <format>

// ------------------------------------------------------------

void* ost::runtime_values::AppInstance = nullptr;
int ost::runtime_values::AppInstanceFlags = 0;


// ------------------------------------------------------------

struct EngineCommandLineContext
{
	EngineCommandLineContext(const ost::SCommandArgs& args)
	{
		auto commandIT = [&](const std::string& cmd, const std::string& val)
			{
				_cmdValues[cmd] = val;
			};

		args.ForeachCommand(commandIT);
	}

	bool TryParseFlt(const std::string& cmd, float& outVal)
	{
		std::string strVal;
		if (TryParseString(cmd, strVal))
		{
			try { outVal = std::stof(strVal); }
			catch (std::exception e)
			{
				return false;
			}
			return true;
		}
		return false;
	}

	bool TryParseInt(const std::string& cmd, int& outVal)
	{
		std::string strVal;
		if (TryParseString(cmd, strVal))
		{
			try { outVal = std::stoi(strVal); }
			catch (std::exception e)
			{
				return false;
			}
			return true;
		}
		return false;
	}

	bool TryParseString(const std::string& cmd, std::string& outVal)
	{
		auto it = _cmdValues.find(cmd);
		if (it != _cmdValues.end())
		{
			outVal = it->second;
			return true;
		}
		return false;
	}
private:
	std::unordered_map<std::string, std::string> _cmdValues;
};

struct EngineConfig
{
	std::string GameModuleName;
	std::string WorkingPath;
	int WindowWidth = 1920;
	int WindowHeight = 1080;

	EngineConfig(EngineCommandLineContext& eclc)
	{
		eclc.TryParseString("-gameMod", GameModuleName);
		eclc.TryParseString("-assetsPath", WorkingPath);
		eclc.TryParseInt("-w", WindowWidth);
		eclc.TryParseInt("-h", WindowHeight);
	}
};

// ------------------------------------------------------------

ost::COstEngine::COstEngine(const SCommandArgs & cmdLineArgs)
{
	CLoggingContext::Create();
	CLoggingContext::Get()->BindLogger(new CLogger_IOStream());
	LOG_INFO("Logging context initialized, bound IOStream Logger");

	// 1. Parse command line args
	EngineCommandLineContext cmdContext{cmdLineArgs};
	const EngineConfig cfg{ cmdContext };

	LOG_INFO("Parsed cmd args");

	// 2. Initialize rendering
	_appWindow = _renderContext.Initialize(cfg.WindowWidth, cfg.WindowHeight);
	LOG_INFO("Created window with dimensions {}x{}", cfg.WindowWidth, cfg.WindowHeight);

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