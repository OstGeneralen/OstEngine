// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "OstEngine/EngineInterface.h"
#include "Engine.h"

// ------------------------------------------------------------

ost::IOstEngine* ost::CreateEngineInstance(SEngineInitializationOptions initOption)
{
	return new COstEngine(initOption);
}

// ------------------------------------------------------------

void ost::ReleaseEngineInstance(IOstEngine** ppEngine)
{
	delete static_cast<COstEngine*>(*ppEngine);
	(*ppEngine) = nullptr;
}

// ------------------------------------------------------------