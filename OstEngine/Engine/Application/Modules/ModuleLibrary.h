// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once
#include "Engine/Application/Modules/ModuleHandle.h"

#include <vector>

namespace ost
{

	class CModuleLibrary
	{
	public:
		void LoadModule( const wchar_t* moduleName, SEngineContext& engineContext );
		void UnloadModule( const wchar_t* moduleName, SEngineContext& engineContext );
		void UnloadAllModules( SEngineContext& engineContext );

		const SModuleHandle& GetHandle( const wchar_t* moduleName );

	private:
		std::vector< SModuleHandle >::iterator FindIfLoaded( const wchar_t* moduleName );
		void UnloadModule( std::vector< SModuleHandle >::iterator moduleIt, SEngineContext& engineContext );

		std::vector< SModuleHandle > _loadedModules;
	};
} // namespace ost