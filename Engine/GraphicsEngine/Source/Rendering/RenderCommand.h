// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <OstTypes.h>

#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    struct Buffer;
    struct Shader;
    struct Texture;

    struct RenderCommand
    {
        Uint64 materialIndex;

        const Buffer* pVertexBuffer;
        const Buffer* pIndexBuffer;

        SizeType indexCount;
        SizeType indexOffset;
        SizeType vertexOffset;

        Matrix4x4 transform;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------