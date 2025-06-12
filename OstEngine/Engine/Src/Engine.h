// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/EngineInterface.h"

#include "OstEngine/Application/Window/Window.h"
#include "Rendering/RenderingContext.h"
#include "Application/Config/EngineConfiguration.h"

// ------------------------------------------------------------

namespace ost
{
	class COstEngine : public IOstEngine
	{
	public:
		COstEngine(SEngineInitializationOptions initOptions);
		int Run() override;
	private:
		SEngineConfigurations _configuration;
		CRenderingContext _renderContext;
		CWindow* _appWindow;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------