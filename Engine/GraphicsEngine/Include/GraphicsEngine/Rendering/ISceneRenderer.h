// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/IGraphicsScene.h"
#include "GraphicsEngine/Resources/Interfaces/IShader.h"

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
        virtual const ITexture* GetTargetTexture(ESceneRendererTargetTexture t) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------