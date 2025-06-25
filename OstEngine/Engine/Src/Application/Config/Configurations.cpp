// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Application/Config/Configurations.h"

#include "OstEngine/Application/Config/CmdArgs.h"
#include "Application/Config/ConfigFile.h"

#include <OstLog/OstLogger.h>

OSTLOG_LOG_INSTANCE(CfgLog);

// ------------------------------------------------------------

namespace
{
	void SetFlag(const std::string& valueStr, bool& valueRef)
	{
		if (valueStr.length() == 0 || valueStr == "true")
		{
			valueRef = true;
		}
		else if (valueStr == "false")
		{
			valueRef = false;
		}
	}

	void SetInt(const std::string& valueStr, ost::int32& valueRef)
	{
		try
		{
			ost::int32 value = std::stoi(valueStr);
			valueRef = value;
		}
		catch (std::exception e)
		{
		}
	}

	void SetFloat(const std::string& valueStr, ost::float32& valueRef)
	{
		try
		{
			ost::float32 value = std::stof(valueStr);
			valueRef = value;
		}
		catch (std::exception e)
		{
		}
	}

	void SetString(const std::string& valueStr, std::string& valueRef)
	{
		if (valueStr.starts_with('\"') && valueStr.ends_with('\"'))
		{
			valueRef = valueStr.substr(1, valueStr.length() - 2);
		}
		else
		{
			valueRef = valueStr;
		}
	}
}

// ------------------------------------------------------------

void ost::SConfig::ParseCommandLine(const SCommandArgs& args)
{
	auto scope = CfgLog.ScopedLog(OstLogLevel::Info, "Parsing command line");
	auto iteration = [&](const auto& cN, const auto& cV) { ForeachConfigValue(cN, cV, scope); };
	args.ForeachCommand(iteration);
}

// ------------------------------------------------------------

void ost::SConfig::ParseConfigFile(const CConfigFile& cfg)
{
	ost::log::SLogScope scope = CfgLog.ScopedLog(OstLogLevel::Info, "Parsing config file");
	auto iteration = [&](const auto& cN, const auto& cV) { ForeachConfigValue(cN, cV, scope); };
	cfg.ForeachConfigValue(iteration);
}

// ------------------------------------------------------------

void ost::SConfig::Register(const std::string& config, bool& value)
{
	_registeredValues[config] = { EValueType::Flag, &value };
}

// ------------------------------------------------------------

void ost::SConfig::Register(const std::string& config, int32& value)
{
	_registeredValues[config] = { EValueType::Integer, &value };
}

// ------------------------------------------------------------

void ost::SConfig::Register(const std::string& config, float32& value)
{
	_registeredValues[config] = { EValueType::Float, &value };
}

// ------------------------------------------------------------

void ost::SConfig::Register(const std::string& config, std::string& value)
{
	_registeredValues[config] = { EValueType::String, &value };
}

// ------------------------------------------------------------

void ost::SConfig::ForeachConfigValue(const std::string& n, const std::string& v, ost::log::SLogScope& logScope)
{
	auto cfIT = _registeredValues.find(n);

	if (cfIT != _registeredValues.end())
	{
		void* valuePtr = cfIT->second.vP;
		const EValueType valType = cfIT->second.vT;

		switch (valType)
		{
		case EValueType::Flag:
		{
			bool& vRef = *static_cast<bool*>(valuePtr);
			::SetFlag(v, vRef);
			logScope.Log("{}: {}", n, vRef);
			break;
		}
		case EValueType::Integer:
		{
			int32& vRef = *static_cast<int32*>(valuePtr);
			::SetInt(v, vRef);
			logScope.Log("{}: {}", n, vRef);
			break;
		}
		case EValueType::Float:
		{
			float32& vRef = *static_cast<float32*>(valuePtr);
			::SetFloat(v, vRef);
			logScope.Log("{}: {}", n, vRef);
			break;
		}
		case EValueType::String:
		{
			std::string& vRef = *static_cast<std::string*>(valuePtr);
			::SetString(v, vRef);
			logScope.Log("{}: {}", n, vRef);
			break;
		}
		}
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------