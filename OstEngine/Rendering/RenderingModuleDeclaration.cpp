#include "RenderingModuleDeclaration.h"
#include "Rendering/RenderingModule.h"

RENDERING_API ost::IModule* CreateModulePtr()
{
	return new ost::CRenderingModule();
}
