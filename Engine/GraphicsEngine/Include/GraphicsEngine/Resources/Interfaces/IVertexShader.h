// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/Interfaces/IGraphicsResource.h"

// ------------------------------------------------------------

namespace ost
{
    DECLARE_GFX_RESOURCE_HANDLE(HVertexShader);

    struct IVertexShader : public IGraphicsResource
    {
        virtual EVertexType GetVertexType() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------