// Kasper "OstGeneralen" Esbjornsson - 2026
#include "EditorContext.h"

using namespace ost;

// ------------------------------------------------------------

EditorContext::EditorContext(ServiceLocator& services, IEditorCommandQueue& cmdQueue, EditorGUI& gui)
    : serviceLocator{services}
    , sceneContext{*this}
    , guiContext{*this, gui}
    , commandQueue{cmdQueue}
{
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------