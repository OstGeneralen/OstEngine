// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once
#include "Engine/Application/Modules/ModuleHandle.h"
#include <Common/Public/Engine/EngineContext.h>
#include <Common/Public/Module/ModuleInterface.h>

#include <string>

namespace ost
{
	class CModuleLoader
	{
	public:
		SModuleHandle LoadModule( const wchar_t* moduleName, SEngineContext& engineContext );
		void UnloadModule( SModuleHandle& modHandle, SEngineContext& engineContext );

	private:
		std::wstring MakeModulePath( const std::wstring& moduleName );
	};
} // namespace ost