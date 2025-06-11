// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/EngineInterface.h"

#include "OstEngine/Application/Window/Window.h"
#include "Rendering/RenderingContext.h"

// ------------------------------------------------------------

namespace ost
{
	class COstEngine : public IOstEngine
	{
	public:
		COstEngine(const SCommandArgs& cmdLineArgs, SEngineInitializationOptions initOptions);
		int Run() override;
	private:
		CRenderingContext _renderContext;
		CWindow* _appWindow;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------