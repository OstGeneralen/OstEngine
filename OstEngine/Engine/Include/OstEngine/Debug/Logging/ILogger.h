// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Debug/Logging/LogMessage.h>

// ------------------------------------------------------------

namespace ost
{
	class ILogger
	{
	public:
		virtual void ReceiveMessage(const SLogMessage& message, uint32 scope = 0) = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------