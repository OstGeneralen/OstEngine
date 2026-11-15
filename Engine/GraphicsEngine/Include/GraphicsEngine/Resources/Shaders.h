// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/IGraphicsResource.h"

#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    DECLARE_GFX_RESOURCE_HANDLE(HVertexShader);
    DECLARE_GFX_RESOURCE_HANDLE(HPixelShader);

    // ------------------------------------------------------------

    struct IVertexShader : public IGraphicsResource
    {
        virtual EVertexType GetVertexType() const = 0;
    };

    // ------------------------------------------------------------

    struct IPixelShader : public IGraphicsResource
    {
        virtual SizeType GetTargetCount() const = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------