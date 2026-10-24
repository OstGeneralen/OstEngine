// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "System/IEditorCommandQueue.h"
#include "Editors/Shared/EditorSceneContext.h"
#include "GUI/GUIContext.h"

#include <Services/ServiceLocator.h>
#include <Memory/UniquePtr.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext
    {
    public:
        EditorContext(ServiceLocator& services, IEditorCommandQueue& cmdQueue, EditorGUI& gui);

        ServiceLocator& serviceLocator;
        GUIContext guiContext;
        EditorSceneContext sceneContext;
        IEditorCommandQueue& commandQueue;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------