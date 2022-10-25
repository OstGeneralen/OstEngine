// OstEngine (c) - Kasper Esbjornsson 2022

#include "CoreEngine.h"

#include <Common/Public/Debugging/Logging/Logging.h>
#include <Common/Public/String/StringHelperLibrary.h>

#include <algorithm>

DEFINE_LOG( EngineBootLog );
DEFINE_LOG( EngineShutdownLog );

void ost::CCoreEngine::Run()
{
	Bootup();

	// while (_shouldRun)
	//{
	//	// Do tick
	// }

	Shutdown();
}

void ost::CCoreEngine::RequestShutdown()
{
	_shouldRun = false;
}

void ost::CCoreEngine::Bootup()
{
	LOG_VERBOSE( EngineBootLog, "OstGine bootup process started" );

	LOG_VERBOSE( EngineBootLog, "Building engine context" );
	context = new SEngineContext( _serviceProvider );

	LOG_VERBOSE( EngineBootLog, "Attempting load of core modules" );
	LoadCoreModules();
}

void ost::CCoreEngine::Shutdown()
{
	LOG_VERBOSE( EngineShutdownLog, "OstGine shutdown process started" );

	LOG_VERBOSE( EngineShutdownLog, "Unloading all currently loaded modules" );
	_moduleLib.UnloadAllModules( *context );
}

void ost::CCoreEngine::LoadCoreModules()
{
	_moduleLib.LoadModule( L"Rendering.ostmod", *context );
	_moduleLib.LoadModule( L"Audio.ostmod", *context );
	_moduleLib.LoadModule( L"Physics.ostmod", *context );
}
