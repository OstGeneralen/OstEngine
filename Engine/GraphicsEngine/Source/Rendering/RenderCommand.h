// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <OstTypes.h>

#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    struct Buffer;
    struct Shader;

    struct RenderCommand
    {
        const Buffer* pVertexBuffer;
        const Buffer* pIndexBuffer;

        const Shader* pVertexShader;
        const Shader* pPixelShader;

        SizeType indexCount;
        SizeType indexOffset;
        SizeType vertexOffset;

        Matrix4x4 transform;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------