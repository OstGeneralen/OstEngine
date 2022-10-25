#pragma once
#include "Engine/Service/ServiceProvider.h"
#include "Engine/Application/Modules/ModuleLoader.h"
#include <vector>


namespace ost
{
	class CCoreEngine
	{
	public:
		void Run();
		void RequestShutdown();

	private:
		void Shutdown();

		void LoadCoreModules();

		void LoadModule(const wchar_t* moduleName);
		void UnloadModule(const wchar_t* moduleName);
		void UnloadModule(std::vector<SModuleHandle>::iterator it);

		CServiceProvider _serviceProvider;
		CModuleLoader _moduleLoader;
		SEngineContext* context;
		std::vector<SModuleHandle> _loadedModules;
		bool _shouldRun = true;
	};
}