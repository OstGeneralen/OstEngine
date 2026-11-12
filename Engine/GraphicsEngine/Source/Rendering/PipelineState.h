// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

// Src
#include "Objects/Shader.h"
#include "Objects/StateObjects.h"
#include "Objects/Texture.h"

// Utility
#include <Container/StackList.h>

// ------------------------------------------------------------

namespace ost
{
    class GraphicsResourceManager;
    class RenderHardwareInterface;

    class PipelineState
    {
    public:
        PipelineState();

        void Apply(const RenderHardwareInterface& rhi);

        EPrimitiveTopology topology;
        EBlendMode blendMode;
        EDepthMode depthMode;

        Shader vertexShader;
        Shader pixelShader;

        Texture targets[8];
        SizeType numTargets;

        Texture depthTarget;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------