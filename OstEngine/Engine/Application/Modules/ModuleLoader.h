#pragma once
#include <string>
#include <Common/Public/Module/ModuleInterface.h>
#include <Common/Public/Engine/EngineContext.h>
#include "Engine/Application/Modules/ModuleHandle.h"

namespace ost
{
	class CModuleLoader
	{
	public:
		  SModuleHandle LoadModule(const wchar_t* moduleName, SEngineContext& engineContext);
		  void UnloadModule(SModuleHandle& modHandle, SEngineContext& engineContext);
	private:

		std::wstring MakeModulePath(const std::wstring& moduleName);
	};
}