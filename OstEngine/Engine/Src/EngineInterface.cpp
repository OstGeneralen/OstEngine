// OstEngine - Copyright(c) 2025 Kasper Esbj�rnsson (MIT License)

#include "OstEngine/EngineInterface.h"
#include "Engine.h"

// ------------------------------------------------------------

ost::IOstEngine* ost::CreateEngineInstance(const SCommandArgs& cmdArgs)
{
	return new COstEngine(cmdArgs);
}

// ------------------------------------------------------------

void ost::ReleaseEngineInstance(IOstEngine** ppEngine)
{
	delete static_cast<COstEngine*>(*ppEngine);
	(*ppEngine) = nullptr;
}

// ------------------------------------------------------------