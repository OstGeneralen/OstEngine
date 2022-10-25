#include "CoreEngine.h"
#include <Common/Public/Debugging/Logging/Logging.h>
#include <Common/Public/String/StringHelperLibrary.h>
#include <algorithm>

DEFINE_LOG(EngineBootLog);
DEFINE_LOG(EngineShutdownLog);

void ost::CCoreEngine::Run()
{
	LOG_VERBOSE(EngineBootLog, "OstGine bootup process started");

	LOG_VERBOSE(EngineBootLog, "Building engine context");
	context = new SEngineContext(_serviceProvider);

	LOG_VERBOSE(EngineBootLog, "Attempting load of core modules");
	LoadCoreModules();

	//while (_shouldRun)
	//{
	//	// Do tick
	//}

	LOG_VERBOSE(EngineShutdownLog, "OstGine shutdown process started");

	LOG_VERBOSE(EngineShutdownLog, "Unloading all currently loaded modules");
	Shutdown();
}

void ost::CCoreEngine::RequestShutdown()
{
	_shouldRun = false;
}

void ost::CCoreEngine::Shutdown()
{
	while (_loadedModules.size() > 0)
	{
		UnloadModule(_loadedModules.end() - 1);
	}

}

void ost::CCoreEngine::LoadCoreModules()
{
	LoadModule(L"Rendering.ostmod");
	LoadModule(L"Audio.ostmod");
	LoadModule(L"Physics.ostmod");
}

void ost::CCoreEngine::LoadModule(const wchar_t* moduleName)
{
	auto compareFunc = [moduleName](const SModuleHandle& c) { return c.ModuleName == stringhelpers::WstrToStr(moduleName); };
	auto found = std::find_if(_loadedModules.begin(), _loadedModules.end(), compareFunc);

	if (found != _loadedModules.end())
	{
		// If this module is already loaded, treat this as a reload and unload it first.
		UnloadModule(found);
	}
	
	auto loadedModule = _moduleLoader.LoadModule(moduleName, *context);

	if (loadedModule.IsValid())
	{
		_loadedModules.push_back(std::move(loadedModule));
	}
}

void ost::CCoreEngine::UnloadModule(const wchar_t* moduleName)
{
	auto compareFunc = [moduleName](const SModuleHandle& c) { return c.ModuleName == stringhelpers::WstrToStr(moduleName); };
	auto found = std::find_if(_loadedModules.begin(), _loadedModules.end(), compareFunc);

	if (found != _loadedModules.end())
	{
		UnloadModule(found);
	}
}

void ost::CCoreEngine::UnloadModule(std::vector<SModuleHandle>::iterator it)
{
	_moduleLoader.UnloadModule(*it, *context);
	_loadedModules.erase(it);
}
