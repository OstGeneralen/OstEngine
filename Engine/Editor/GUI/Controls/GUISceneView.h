// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GUI/GUIControl.h"

// ------------------------------------------------------------

namespace ost
{
    class GUISceneView : public GUIControl
    {
    public:
        GUISceneView();
        void Display() override;
    private:
        Uint32 _displayTexture;
        Vector2u _cachedSceneRenderSize;
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------