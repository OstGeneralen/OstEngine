// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IRenderScene.h"
#include "GraphicsEngine/Resources/ITexture.h"

// ------------------------------------------------------------

namespace ost
{
    enum class ESceneRendererTargetTexture
    {
        Albedo,
        Normal,
        ORM,
        Depth,
        Output,
    };

    class ISceneRenderer
    {
    public:
        virtual IRenderScene& GetRenderScene() = 0;
        virtual const ITexture* GetTargetTexture(ESceneRendererTargetTexture t) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------