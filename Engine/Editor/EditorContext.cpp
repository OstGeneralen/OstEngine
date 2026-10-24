// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorContext.h"

using namespace ost;

// ------------------------------------------------------------

EditorContext::EditorContext(ServiceLocator& services, IEditorCommandQueue& cmdQueue, EditorGUI& gui, IGraphicsEngine& gfxEngine)
    : serviceLocator{services}
    , sceneContext{*this}
    , sceneViewContext{*this, gfxEngine}
    , guiContext{*this, gui}
    , commandQueue{cmdQueue}
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------