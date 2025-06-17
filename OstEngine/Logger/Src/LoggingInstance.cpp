// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstLog/LoggingInstance.h"
#include "OstLog/ILogger.h"

// ------------------------------------------------------------

ost::log::CLogInstance::CLogInstance(std::string instanceName)
	: _instanceName(instanceName)
	, _currentMessage{}
	, _currentMessageScope{nullptr}
{
}

// ------------------------------------------------------------

void ost::log::CLogInstance::BeginLogScope( const SLogMessage& scopeRootMsg)
{
	_currentMessage = scopeRootMsg;
	_currentMessageScope = &_currentMessage;
}

// ------------------------------------------------------------

void ost::log::CLogInstance::EndScope()
{
	_currentMessageScope = nullptr;
	Log(_currentMessage);
	_currentMessage = {};
}

// ------------------------------------------------------------

void ost::log::CLogInstance::Log(const SLogMessage& msg)
{
	if (_currentMessageScope == nullptr)
	{
		GetLogger().Log(msg);
	}
	else
	{
		_currentMessageScope->SubMessages.push_back(msg);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------