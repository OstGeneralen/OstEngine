// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstLog/Logging/LogScope.h"
#include "OstLog/Logging/LoggerAPI.h"
#include "OstLog/Logging/ILogger.h"

// ------------------------------------------------------------

ost::log::SLogScope::SLogScope(SLogMessage rootMessage)
	: _rootMessage(rootMessage)
	, _isValid(true)
{
}

// ------------------------------------------------------------

ost::log::SLogScope::SLogScope(SLogScope&& o) noexcept
	: _rootMessage(std::move(o._rootMessage))
	, _isValid(true)
{
	o._isValid = false;
}

// ------------------------------------------------------------

ost::log::SLogScope::~SLogScope()
{
	if (_isValid)
	{
		GetLogger().Log(_rootMessage);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------