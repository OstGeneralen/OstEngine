// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Debug/Logging/ILogger.h"
#include <vector>

// ------------------------------------------------------------

namespace ost
{
	struct SLogMessage;

	class CLoggingContext
	{
	public:
		static void Create();
		static void Bind(CLoggingContext* context);
		static CLoggingContext* Get();

		static void PushLogMessage(const SLogMessage& lm);
	private:
		static CLoggingContext* s_pInstance;
		static bool s_instanceBound;

	public:
		void BindLogger(ILogger* pLogger);
		void Instance_PushLogMessage(const SLogMessage& lm);

	private:
		std::vector<ILogger*> _loggers;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------