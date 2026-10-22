// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"

// ------------------------------------------------------------

namespace ost
{   
    class SceneEditorContext;

    class GUIActorEditor : public GUIControl
    {
    public:
        GUIActorEditor( SceneEditorContext& sceneEditCtx );

        void Display() override;

    private:
        SceneEditorContext& _sceneEditorCtx;

    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------