// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Logger.h"

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

ost::log::CLogger::CLogger()
	: _messageQueue{64}
{
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
	_logThread = std::thread(&CLogger::LoggingRun, this);
	GetLogger().INFO("OstLogger INITIALIZED, RUNNING ON LOGGING THREAD");
}

// ------------------------------------------------------------

void ost::log::CLogger::SignalShutdown()
{
	GetLogger().DEBUG("OstLogger SHUTDOWN SIGNAL RECEIVED");
	_shutdownFlag = true;
}

// ------------------------------------------------------------

void ost::log::CLogger::AwaitShutdown()
{
	GetLogger().INFO("OstLogger AWAITING SHUTDOWN");
	_logThread.join();
	GetLogger().INFO("OstLogger SHUTDOWN COMPLETE");
	// Manually run one last log to confirm the shutdown
	FlushQueue();
}

// ------------------------------------------------------------

void ost::log::CLogger::Log(const SLogMessage& msg)
{
	_messageQueue.Push(msg);
}

// ------------------------------------------------------------

void ost::log::CLogger::LoggingRun()
{
	SLogMessage poppedMessage;
	while (!_shutdownFlag)
	{
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
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------