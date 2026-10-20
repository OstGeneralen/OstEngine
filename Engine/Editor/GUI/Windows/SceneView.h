// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class SceneView
    {
    public:
        SceneView();

        void Display();

    private:
        Vector2u _cachedSize;
        Uint32 _displayTexture = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------