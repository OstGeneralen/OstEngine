// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

#include "OstEngine/Application/Config/CmdArgs.h"

// ------------------------------------------------------------

namespace ost
{
	class IOstEngine;

	struct SEngineRuntimeInfo
	{
		void* AppInstancePtr;
		int AppInstanceFlag;
	};


	extern IOstEngine* CreateEngineInstance(const SCommandArgs& cmdArgs);
	extern void ReleaseEngineInstance(IOstEngine** ppEngInstance);

	class IOstEngine
	{
	public:
		virtual int Run() = 0;
	};

}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------