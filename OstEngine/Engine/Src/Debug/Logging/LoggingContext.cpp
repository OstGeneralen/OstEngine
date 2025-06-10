// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Debug/Logging/LoggingContext.h"
#include "OstEngine/Debug/Logging/LogMessage.h"

// ------------------------------------------------------------

ost::CLoggingContext* ost::CLoggingContext::s_pInstance = nullptr;
bool ost::CLoggingContext::s_instanceBound = false;

// ------------------------------------------------------------

void ost::CLoggingContext::Create()
{
	s_pInstance = new CLoggingContext();
	s_instanceBound = false;
}

// ------------------------------------------------------------

void ost::CLoggingContext::Bind(CLoggingContext* context)
{
	s_pInstance = context;
	s_instanceBound = true;
}

// ------------------------------------------------------------

ost::CLoggingContext* ost::CLoggingContext::Get()
{
	return s_pInstance;
}

// ------------------------------------------------------------

void ost::CLoggingContext::PushLogMessage(const SLogMessage& msg)
{
	if (s_pInstance != nullptr)
	{
		s_pInstance->Instance_PushLogMessage(msg);
	}
}

// ------------------------------------------------------------

void ost::CLoggingContext::BindLogger(ILogger* pLogger)
{
	_loggers.push_back(pLogger);
}

// ------------------------------------------------------------

void ost::CLoggingContext::Instance_PushLogMessage(const SLogMessage& msg)
{
	for (ILogger* l : _loggers)
	{
		l->ReceiveMessage(msg);
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------