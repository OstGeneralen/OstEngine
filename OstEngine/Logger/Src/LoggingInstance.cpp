// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstLog/Logging/LoggingInstance.h"
#include "OstLog/Logging/ILogger.h"

// ------------------------------------------------------------

ost::log::CLogInstance::CLogInstance(std::string instanceName)
	: _instanceName(instanceName)
	, _activeScope{nullptr}
{
}

// ------------------------------------------------------------

void ost::log::CLogInstance::Log(const SLogMessage& msg)
{
	if (_activeScope != nullptr)
	{
		_activeScope->Log(msg);
	}
	else
	{
		GetLogger().Log(msg);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------