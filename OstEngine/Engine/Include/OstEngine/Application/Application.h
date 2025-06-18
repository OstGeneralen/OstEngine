// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Application/Config/CmdArgs.h"
#include "OstEngine/EngineInterface.h"


// ------------------------------------------------------------

namespace ost
{
	class CAppWindow;
	class COstEngine;

	class CApplication
	{
	public:
		CApplication( const SCommandArgs& cmdArgs );
		~CApplication();

		void Run();
	private:
		COstEngine* _enginePtr;
		CAppWindow* _appWindowPtr;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------