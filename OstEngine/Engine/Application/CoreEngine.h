// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once
#include "Engine/Application/Modules/ModuleLibrary.h"
#include "Engine/Service/ServiceProvider.h"

#include <vector>

namespace ost
{
	class CCoreEngine
	{
	public:
		void Run();
		void RequestShutdown();

	private:
		void Bootup();
		void Shutdown();
		void LoadCoreModules();

		SEngineContext* context;
		CServiceProvider _serviceProvider;
		CModuleLibrary _moduleLib;

		bool _shouldRun = true;
	};
} // namespace ost