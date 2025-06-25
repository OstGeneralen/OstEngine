// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Logger.h"
#include <OstLog/Logging/LoggingInstance.h>

// ------------------------------------------------------------
// API Functions
// ------------------------------------------------------------
ost::log::CLogger s_LogInstance;

extern "C" LOGGER_API ost::log::ILogger& GetLogger()
{
	return s_LogInstance;
}

extern "C" LOGGER_API void OstLogger_RegisterLogSink(ost::log::CLogSink& sink)
{
	s_LogInstance.RegisterSink(sink);
}

extern "C" LOGGER_API void OstLogger_RunLogger()
{
	s_LogInstance.Run();
}

extern "C" LOGGER_API void OstLogger_PostShutdownSignal()
{
	s_LogInstance.SignalShutdown();
}

extern "C" LOGGER_API void OstLogger_AwaitShutdown()
{
	s_LogInstance.AwaitShutdown();
}

// ------------------------------------------------------------
// CLogger Definition
// ------------------------------------------------------------

ost::log::CLogInstance OstLogInstance("OstLog");

ost::log::CLogger::CLogger()
	: _messageQueue{LOG_THREAD_SIZE}
	, _threadSemaphore{0}
{
}

// ------------------------------------------------------------

ost::log::CLogger::~CLogger()
{
	if (_running)
	{
		SignalShutdown();
		AwaitShutdown();
	}
}

// ------------------------------------------------------------

void ost::log::CLogger::RegisterSink(CLogSink& sink)
{
	_sinks.push_back(&sink);
}

// ------------------------------------------------------------

void ost::log::CLogger::Run()
{
	_shutdownFlag = false;
	_running = true;
	_logThread = std::thread(&CLogger::LoggingRun, this);
	OstLogInstance.Log(ELogLevel::Info, "INITIALIZED, RUNNING ON LOGGING THREAD");
}

// ------------------------------------------------------------

void ost::log::CLogger::SignalShutdown()
{
	OstLogInstance.Log(ELogLevel::Debug, "SHUTDOWN SIGNAL RECEIVED");
	_shutdownFlag = true;
	_threadSemaphore.release(); // Notify the semaphore to ensure we actually exit out of the execution loop
}

// ------------------------------------------------------------

void ost::log::CLogger::AwaitShutdown()
{
	OstLogInstance.Log(ELogLevel::Info, "AWAITING SHUTDOWN");
	_logThread.join();
	OstLogInstance.Log(ELogLevel::Info, "SHUTDOWN COMPLETE");
	// Manually run one last log to confirm the shutdown
	FlushQueue();
	_running = false;
}

// ------------------------------------------------------------

void ost::log::CLogger::Log(const SLogMessage& msg)
{
	_messageQueue.Push(msg);
	_threadSemaphore.release();
}

// ------------------------------------------------------------

void ost::log::CLogger::LoggingRun()
{
	SLogMessage poppedMessage;
	while (!_shutdownFlag)
	{
		_threadSemaphore.acquire();

		if (_messageQueue.Pop(poppedMessage))
		{
			for (auto ptrSink : _sinks)
			{
				if (ptrSink->FilterLogLevel(poppedMessage.Level))
				{
					ptrSink->Log(poppedMessage);
				}
			}
		}
	}
}

// ------------------------------------------------------------

void ost::log::CLogger::FlushQueue()
{
	SLogMessage msg;
	while (_messageQueue.Pop(msg))
	{
		for (auto ptrSink : _sinks)
		{
			if (ptrSink->FilterLogLevel(msg.Level))
			{
				ptrSink->Log(msg);
			}
		}
	}

	for (auto ptrSink : _sinks)
	{
		ptrSink->Flush();
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------