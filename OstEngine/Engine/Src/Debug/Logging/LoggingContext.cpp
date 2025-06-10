// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Debug/Logging/LoggingContext.h"

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
// ------------------------------------------------------------
// ------------------------------------------------------------