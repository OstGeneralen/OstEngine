#pragma once
#include "Rendering/RenderingModuleDeclaration.h"
#include <Common/Public/Engine/Service/ServiceInterface.h>

namespace ost
{
	class RENDERING_API ITestRenderingService : public IService
	{
	public:
		virtual void CallMe() = 0;
	};

	class RENDERING_API CTestRenderingService : public ITestRenderingService
	{
	public:
		void CallMe() override;
	};
}