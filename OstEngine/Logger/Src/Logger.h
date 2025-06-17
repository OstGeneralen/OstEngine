// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/LoggerApi.h"
#include "OstLog/ILogger.h"
#include "OstLog/Sinks/LogSink.h"
#include "Internal/MessageQueue.h"

#include <vector>
#include <thread>
#include <atomic>
#include <semaphore>

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class CLogger final : public ILogger
		{
		public:
			CLogger();
			void RegisterSink(CLogSink& sink);
			void Run();
			void SignalShutdown();
			void AwaitShutdown();
		
		private:
			void Log(const SLogMessage& msg) override;
			void LoggingRun();
			void FlushQueue();

		private:
			constexpr static size_t LOG_THREAD_SIZE = 128;

			CMessageQueue _messageQueue;
			std::thread _logThread;
			std::counting_semaphore<LOG_THREAD_SIZE> _threadSemaphore;
			std::atomic_bool _shutdownFlag{ false };
			std::vector<CLogSink*> _sinks;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------