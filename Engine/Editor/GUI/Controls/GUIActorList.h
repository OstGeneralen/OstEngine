// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"

// ------------------------------------------------------------

namespace ost
{
    class SceneEditorContext;
    class Actor;

    class GUIActorList : public GUIControl
    {
    public:
        GUIActorList(SceneEditorContext& sceneEditorCtx);
        void Display() override;

    private:
        void DisplayActor(Actor& actor, bool hovered, bool selected);
        SceneEditorContext& _sceneEditorCtx;
        Actor* _pCurrentSelectedActor = nullptr;
        Actor* _pCurrentHoveredActor = nullptr;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------