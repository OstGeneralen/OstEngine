// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Resources/ShaderCPUData.h"
#include "GraphicsEngine/Resources/VertexElement.h"

#include <OstTypes.h>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{

    struct PipelineStateDesc
    {
        List<VertexElement> vertexLayout;
        ShaderCPUData vsData;
        ShaderCPUData psData;
        EBlendState blendState = EBlendState::Opaque;
        EPrimitiveTopology topology = EPrimitiveTopology::TriangleList;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------