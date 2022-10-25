// OstEngine (c) - Kasper Esbjornsson 2022

#include "Rendering/RenderingModule.h"

#include <Common/Public/Debugging/Logging/Logging.h>

#pragma comment( lib, "Commonx64_Debug" )

DEFINE_LOG( RenderingModuleLog );

void ost::CRenderingModule::Load( SEngineContext& context )
{
	LOG_CONFIRM( RenderingModuleLog, "Rendering module was loaded!" );
}

void ost::CRenderingModule::Unload( SEngineContext& context ) { }