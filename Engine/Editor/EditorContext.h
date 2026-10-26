// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Editors/SceneView/SceneViewContext.h"
#include "Editors/Shared/EditorSceneContext.h"
#include "Editors/AssetView/Context/EditorAssetContext.h"
#include "GUI/GUIContext.h"
#include "System/IEditorCommandQueue.h"

#include <Memory/UniquePtr.h>
#include <Services/ServiceLocator.h>

// ------------------------------------------------------------

namespace ost
{
    struct EditorContext
    {
    public:
        EditorContext(ServiceLocator& services, IEditorCommandQueue& cmdQueue, EditorGUI& gui, IGraphicsEngine& gfxEngine);

        ServiceLocator& serviceLocator;
        GUIContext guiContext;
        SceneViewContext sceneViewContext;
        EditorSceneContext sceneContext;
        EditorAssetContext assetContext;
        IEditorCommandQueue& commandQueue;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------