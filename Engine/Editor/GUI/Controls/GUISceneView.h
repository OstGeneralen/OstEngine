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
        void PostDisplay() override;

    private:
        void UpdateFlyMode();
        
        bool _isFlyMode = false;
        Vector2f _cachedMousePos;


        Uint32 _displayTexture;
        Vector2u _cachedSceneRenderSize;
        Vector2u _desiredRenderSize;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------