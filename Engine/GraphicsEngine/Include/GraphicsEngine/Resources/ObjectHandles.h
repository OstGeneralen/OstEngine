// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

#include <Utility/TypedIntegerHandle.h>

// ------------------------------------------------------------

namespace ost
{
    using HTexture = TypedIntegerHandle<struct HNDType_Texture>;
    using HPipelineState = TypedIntegerHandle<struct HNDType_PSO>;
    using HMesh = TypedIntegerHandle<struct HNDType_Mesh>;
    using HShader = TypedIntegerHandle<struct HNDType_Shader>;
    using HUniformBuffer = TypedIntegerHandle<struct HNDType_UniformBuffer>;
    using HVertexBuffer = TypedIntegerHandle<struct HNDType_VertexBuffer>;
    using HIndexBuffer = TypedIntegerHandle<struct HNDType_IndexBuffer>;
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------