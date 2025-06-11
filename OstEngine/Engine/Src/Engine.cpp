// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "Engine.h"
#include "Application/AppRuntimeStatics.h"

#include "OstEngine/Debug/Logging/LoggingContext.h"
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
		if (eclc.TryParseString("-gameMod", GameModuleName))
			LOG_DETAIL("Cmd Arg: Parsed -gameMod arg, value '{}'", GameModuleName);

		if (eclc.TryParseString("-assetsPath", WorkingPath))
			LOG_DETAIL("Cmd Arg: Parsed -assetPath arg, value '{}'", WorkingPath);

		if (eclc.TryParseInt("-w", WindowWidth))
			LOG_DETAIL("Cmd Arg: Parsed -w arg, value '{}'", WindowWidth);

		if (eclc.TryParseInt("-h", WindowHeight))
			LOG_DETAIL("Cmd Arg: Parsed -h arg, value '{}'", WindowWidth);
	}
};

// ------------------------------------------------------------

ost::COstEngine::COstEngine(const SCommandArgs& cmdLineArgs, SEngineInitializationOptions initOptions)
{
	CLoggingContext::Create();
	if (initOptions.InitLogger != nullptr)
	{
		CLoggingContext::Get()->BindLogger(initOptions.InitLogger);
	}
	LOG_INFO("OstEngine created with command line args");
	LOG_BEGIN_SCOPE();

	cmdLineArgs.ForeachCommand([](const std::string msg, const std::string val) {
		if (val.length() > 0)
		{
			LOG_INFO("{} = {}", msg, val);
		}
		else
		{
			LOG_INFO(msg);
		}
		});
	LOG_END_SCOPE();

	LOG_DETAIL("Logging context initialized");

	// 1. Parse command line args
	EngineCommandLineContext cmdContext{ cmdLineArgs };
	const EngineConfig cfg{ cmdContext };

	// 2. Initialize rendering
	_appWindow = _renderContext.Initialize(cfg.WindowWidth, cfg.WindowHeight);
	LOG_CONFIRM("Created window with dimensions {}x{}", cfg.WindowWidth, cfg.WindowHeight);

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