// OstEngine (c) - Kasper Esbjornsson 2022

#include "ModuleLoader.h"

#include <Common/Public/Debugging/Logging/Logging.h>
#include <Common/Public/Module/ModuleInterface.h>
#include <Common/Public/String/StringHelperLibrary.h>

#include <windows.h>

DEFINE_LOG( ModuleHandlerLog );

using namespace ost;

typedef IModule*( __stdcall* f_MakeModulePtr )();

ost::SModuleHandle ost::CModuleLoader::LoadModule( const wchar_t* moduleName, SEngineContext& engineContext )
{
	const std::wstring modulePath = MakeModulePath( moduleName );

	LOG_MESSAGE( ModuleHandlerLog, "Starting load for module '{}'. Expected path: '{}'", stringhelpers::WstrToStr( moduleName ), stringhelpers::WstrToStr( modulePath ) );

	HINSTANCE moduleInstance = LoadLibrary( modulePath.c_str() );
	if ( !moduleInstance )
	{
		LOG_ERROR( ModuleHandlerLog, "Could not find module '{}' at path '{}'", stringhelpers::WstrToStr( moduleName ), stringhelpers::WstrToStr( modulePath ) );
		return SModuleHandle::MakeInvalid();
	}

	f_MakeModulePtr MakeModulePtr = (f_MakeModulePtr)GetProcAddress( moduleInstance, "CreateModulePtr" );

	if ( !MakeModulePtr )
	{
		LOG_ERROR( ModuleHandlerLog, "Could not find CreateModulePtr function for module '{}'", stringhelpers::WstrToStr( moduleName ) );
		FreeLibrary( moduleInstance );
		return SModuleHandle::MakeInvalid();
	}

	ost::IModule* modulePtr = MakeModulePtr();
	modulePtr->Load( engineContext );

	LOG_CONFIRM( ModuleHandlerLog, "Successfully loaded module '{}'", stringhelpers::WstrToStr( moduleName ) );

	return std::move( SModuleHandle( ost::stringhelpers::WstrToStr( moduleName ), modulePtr, moduleInstance ) );
}

void ost::CModuleLoader::UnloadModule( SModuleHandle& modHandle, SEngineContext& engineContext )
{
	LOG_MESSAGE( ModuleHandlerLog, "Unloading module '{}'", modHandle.ModuleName );

	modHandle.ModulePtr->Unload( engineContext );
	delete modHandle.ModulePtr;

	int x = FreeLibrary( (HINSTANCE)modHandle.InstancePtr );

	modHandle.InstancePtr = nullptr;
	modHandle.ModulePtr = nullptr;
}

std::wstring ost::CModuleLoader::MakeModulePath( const std::wstring& moduleName )
{
	std::wstring modulesPath;

#ifdef _DEBUG
	modulesPath = L"Modules\\Debug\\";
#else
	modulesPath = "Modules\\Release\\";
#endif

	return std::move( std::wstring( modulesPath + moduleName ) );
}
