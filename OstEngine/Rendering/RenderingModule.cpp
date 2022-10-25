#include "Rendering/RenderingModule.h"
#include <Common/Public/Debugging/Logging/Logging.h>
#include "Rendering/Public/TestService.h"

#pragma comment(lib, "Commonx64_Debug")

DEFINE_LOG(RenderingModuleLog);


void ost::CRenderingModule::Load(SEngineContext& context)
{
	LOG_CONFIRM(RenderingModuleLog, "Rendering module was loaded!");
	
	_testService = new CTestRenderingService();
	context.ServiceProvider.RegisterService<ITestRenderingService>(_testService);
}

void ost::CRenderingModule::Unload(SEngineContext& context)
{
	context.ServiceProvider.RemoveService<ITestRenderingService>();
}