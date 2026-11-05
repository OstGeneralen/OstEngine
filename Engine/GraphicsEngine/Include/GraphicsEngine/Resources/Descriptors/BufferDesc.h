// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Vertex.h"

#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    struct VertexBufferDesc
    {
        EVertexType vertexType;
        const void* pVertexData;
        SizeType numVertices;
    };

    struct IndexBufferDesc
    {
        const Uint32* pIndexData;
        SizeType numIndices;
    };

    struct UniformBufferDesc
    {
        const void* pData;
        SizeType numBytes;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------