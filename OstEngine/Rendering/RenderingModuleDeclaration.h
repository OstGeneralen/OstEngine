// OstEngine (c) - Kasper Esbjornsson 2022

#pragma once

#include <Common/Public/Module/ModuleInterface.h>

#ifdef OstMod_Rendering
#define RENDERING_API __declspec( dllexport )
#else
#define RENDERING_API __declspec( dllimport )
#endif

extern "C"
{
	RENDERING_API ost::IModule* CreateModulePtr();
}