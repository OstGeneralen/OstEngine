// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstLog/Logging/LogScope.h"
#include "OstLog/Logging/LoggerAPI.h"
#include "OstLog/Logging/ILogger.h"
#include "OstLog/Logging/LoggingInstance.h"

// ------------------------------------------------------------

ost::log::SLogScope::SLogScope(SLogMessage rootMessage, CLogInstance* instancePtr)
	: _rootMessage(rootMessage)
	, _instancePtr{instancePtr}
{
}

// ------------------------------------------------------------

ost::log::SLogScope::SLogScope(SLogScope&& o) noexcept
	: _rootMessage(std::move(o._rootMessage))
	, _instancePtr{o._instancePtr}
{
	o._instancePtr = nullptr;
	_instancePtr->_activeScope = this;
}

// ------------------------------------------------------------

ost::log::SLogScope::~SLogScope()
{
	if (_instancePtr != nullptr)
	{
		_instancePtr->_activeScope = nullptr;
		GetLogger().Log(_rootMessage);
	}
}

// ------------------------------------------------------------

void ost::log::SLogScope::Log(const SLogMessage& msg)
{
	_rootMessage.SubMessages.push_back(msg);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------