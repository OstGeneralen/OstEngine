// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"
#include <Math/Vector3.h>

// ------------------------------------------------------------

namespace ost
{   
    class SceneEditorContext;
    class Actor;

    class GUIActorEditor : public GUIControl
    {
    public:
        GUIActorEditor( SceneEditorContext& sceneEditCtx );

        void Display() override;

    private:
        void NewTargetActor();

        SceneEditorContext& _sceneEditorCtx;
        Vector3f _cachedEulers;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------