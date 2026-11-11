// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

// ------------------------------------------------------------

namespace ost
{
    struct RenderStateDesc
    {
        EVertexType vertexType;

        HShader vertexShader;
        HShader pixelShader;

        EBlendState blendMode;
        EPrimitiveTopology topology;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------