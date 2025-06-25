// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/APIDefinition.h"

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class ILogger;
	}
}

extern "C" LOGGER_API ost::log::ILogger& GetLogger();


// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------