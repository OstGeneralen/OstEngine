// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/Game/Core/NameComponent.h>

#include <OstLog/OstLogger.h>

OSTLOG_LOG_INSTANCE(NameCompTickLog);

void ost::CNameComponent::Tick()
{
	NameCompTickLog.Log(OstLogLevel::Debug, "COMPONENT WAS TICKED");
}