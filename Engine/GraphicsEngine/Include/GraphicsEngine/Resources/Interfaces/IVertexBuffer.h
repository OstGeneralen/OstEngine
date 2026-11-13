// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/Interfaces/IGraphicsResource.h"

// ------------------------------------------------------------

namespace ost
{
    DECLARE_GFX_RESOURCE_HANDLE(HVertexBuffer);

    struct IVertexBuffer : public IGraphicsResource
    {
        virtual EVertexType GetVertexType() const = 0;
        virtual SizeType GetVertexByteSize() const = 0;
        virtual SizeType GetVertexCount() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------