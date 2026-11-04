// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Vertex.h"
#include "Objects/Buffer.h"

#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    struct Mesh
    {
        Mesh();
        Mesh(const Mesh&);
        Mesh(Mesh&&) noexcept;
        ~Mesh();

        Mesh& operator=(const Mesh&);
        Mesh& operator=(Mesh&&) noexcept;

        EVertexType vertexType;
        Buffer vertexBuffer;
        Buffer indexBuffer;

        SizeType numIndices;
        SizeType indexOffset;
        SizeType vertexOffset;

        SizeType materialIndex;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------