// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)

#include "OstEngine/EngineInterface.h"
#include "Engine.h"

// ------------------------------------------------------------

ost::IOstEngine* ost::CreateEngineInstance(const SCommandArgs& cmdArgs, SEngineInitializationOptions initOption)
{
	return new COstEngine(cmdArgs, initOption);
}

// ------------------------------------------------------------

void ost::ReleaseEngineInstance(IOstEngine** ppEngine)
{
	delete static_cast<COstEngine*>(*ppEngine);
	(*ppEngine) = nullptr;
}

// ------------------------------------------------------------