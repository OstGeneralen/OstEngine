// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Debug/Logging/ILogger.h"

#include <iostream>

// ------------------------------------------------------------

namespace ost
{
	class CLogger_IOStream : public ILogger
	{
	public:
		void ReceiveMessage(const SLogMessage& msg) override
		{
			std::cout << '[' << msg.FormatTimestamp(ETimestampFormat::HH_MM_SS) << "] " << msg.Message << std::endl;
		}
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------