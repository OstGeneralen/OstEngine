// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/LoggerApi.h"
#include "OstLog/ILogger.h"
#include "Internal/MessageQueue.h"

#include <vector>
#include <thread>
#include <atomic>

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class CLogger final : public ILogger
		{
		public:
			CLogger();
			virtual void RegisterSink(CLogSink& sink) override;
			void Run() override;
			void SignalShutdown() override;
			virtual void AwaitShutdown() override;
		
		private:
			void Log(const SLogMessage& msg) override;
			void LoggingRun();
			void FlushQueue();

		private:
			CMessageQueue _messageQueue;
			std::thread _logThread;
			std::atomic_bool _shutdownFlag{ false };
			std::vector<CLogSink*> _sinks;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------