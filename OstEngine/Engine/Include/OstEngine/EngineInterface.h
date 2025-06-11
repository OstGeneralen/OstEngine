// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

#include "OstEngine/Application/Config/CmdArgs.h"

// ------------------------------------------------------------

namespace ost
{
	class IOstEngine;
	class ILogger;

	struct SEngineInitializationOptions
	{
		const SCommandArgs* CmdLineArgs{ nullptr };
		ILogger* InitLogger{ nullptr };
	};


	extern IOstEngine* CreateEngineInstance(SEngineInitializationOptions options);
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