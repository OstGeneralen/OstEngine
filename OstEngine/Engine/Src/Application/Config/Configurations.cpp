// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Application/Config/Configurations.h"

#include "OstEngine/Application/Config/CmdArgs.h"
#include "Application/Config/ConfigFile.h"

#include <OstLog/LoggerAPI.h>
#include <OstLog/ILogger.h>

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
		valueRef = valueStr;
	}
}

// ------------------------------------------------------------

void ost::SConfig::ParseCommandLine(const SCommandArgs& args)
{
	auto iteration = [&](const auto& cN, const auto& cV) { ForeachConfigValue(cN, cV); };

	GetLogger().INFO("Configurations: Parsing command line");
	args.ForeachCommand(iteration);
}

// ------------------------------------------------------------

void ost::SConfig::ParseConfigFile(const CConfigFile& cfg)
{
	GetLogger().INFO("Configurations: Parsing config file");
	auto iteration = [&](const auto& cN, const auto& cV) { ForeachConfigValue(cN, cV); };
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

void ost::SConfig::ForeachConfigValue(const std::string& n, const std::string& v)
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
			GetLogger().INFO("{}: {}", n, vRef);
			break;
		}
		case EValueType::Integer:
		{
			int32& vRef = *static_cast<int32*>(valuePtr);
			::SetInt(v, vRef);
			GetLogger().INFO("{}: {}", n, vRef);
			break;
		}
		case EValueType::Float:
		{
			float32& vRef = *static_cast<float32*>(valuePtr);
			::SetFloat(v, vRef);
			GetLogger().INFO("{}: {}", n, vRef);
			break;
		}
		case EValueType::String:
		{
			std::string& vRef = *static_cast<std::string*>(valuePtr);
			::SetString(v, vRef);
			GetLogger().INFO("{}: {}", n, vRef);
			break;
		}
		}
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------