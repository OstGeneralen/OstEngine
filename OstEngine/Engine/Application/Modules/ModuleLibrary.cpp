// OstEngine (c) - Kasper Esbjornsson 2022

#include "Engine/Application/Modules/ModuleLibrary.h"

#include "Engine/Application/Modules/ModuleLoader.h"
#include <Common/Public/Debugging/Logging/Logging.h>
#include <Common/Public/String/StringHelperLibrary.h>

#include <algorithm>

namespace
{
	ost::SModuleHandle InvalidModuleHandle = ost::SModuleHandle::MakeInvalid();
}

DEFINE_LOG( ModuleLibLog );

void ost::CModuleLibrary::LoadModule( const wchar_t* moduleName, SEngineContext& engineContext )
{
	auto loadedCheckIterator = FindIfLoaded( moduleName );

	if ( loadedCheckIterator != _loadedModules.end() )
	{
		LOG_MESSAGE( ModuleLibLog, "Module '{}' already loaded. Reloading.", stringhelpers::WstrToStr( moduleName ) );

		// This module is already loaded, so treat this as a reload.
		UnloadModule( loadedCheckIterator, engineContext );
	}

	CModuleLoader loader;
	SModuleHandle handle = loader.LoadModule( moduleName, engineContext );

	if ( handle.IsValid() )
	{
		_loadedModules.push_back( handle );
	}
}

void ost::CModuleLibrary::UnloadModule( const wchar_t* moduleName, SEngineContext& engineContext )
{
	auto loadedCheckIterator = FindIfLoaded( moduleName );

	if ( loadedCheckIterator == _loadedModules.end() )
	{
		LOG_WARNING( ModuleLibLog, "Tried unloading a module that wasn't loaded." );
	}
	else
	{
		UnloadModule( loadedCheckIterator, engineContext );
	}
}

void ost::CModuleLibrary::UnloadAllModules( SEngineContext& engineContext )
{
	while ( _loadedModules.size() > 0 )
	{
		UnloadModule( _loadedModules.end(), engineContext );
	}
}

const ost::SModuleHandle& ost::CModuleLibrary::GetHandle( const wchar_t* moduleName )
{
	auto loadedCheckIterator = FindIfLoaded( moduleName );
	return loadedCheckIterator == _loadedModules.end() ? ::InvalidModuleHandle : *loadedCheckIterator;
}

std::vector< ost::SModuleHandle >::iterator ost::CModuleLibrary::FindIfLoaded( const wchar_t* moduleName )
{
	auto findModule = [moduleName]( const SModuleHandle& h )
	{
		return h.ModuleName == stringhelpers::WstrToStr( moduleName );
	};
	return std::find_if( _loadedModules.begin(), _loadedModules.end(), findModule );
}

void ost::CModuleLibrary::UnloadModule( std::vector< SModuleHandle >::iterator moduleIt, SEngineContext& engineContext )
{
	CModuleLoader loader;
	loader.UnloadModule( *moduleIt, engineContext );
	_loadedModules.erase( moduleIt );
}
