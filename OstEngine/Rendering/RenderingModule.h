#pragma once

#include <Common/Public/Module/ModuleInterface.h>
#include "Rendering/Public/TestService.h"

namespace ost
{
	class CRenderingModule : public IModule
	{
	public:
		void Load(SEngineContext& context) override;
		void Unload(SEngineContext& context) override;
	private:
		CTestRenderingService* _testService;
	};
}