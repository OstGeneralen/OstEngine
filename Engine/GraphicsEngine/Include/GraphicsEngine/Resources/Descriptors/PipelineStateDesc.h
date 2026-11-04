// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Resources/Descriptors/ShaderDesc.h"
#include "GraphicsEngine/Resources/VertexElement.h"
#include "GraphicsEngine/Rendering/Vertex.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct PipelineStateDesc
    {
        static List<VertexElement> DefaultVertexLayout_Surface();
        static List<VertexElement> DefaultVertexLayout_Blit();

        List<VertexElement> vertexLayout;
        ShaderDesc vsDesc;
        ShaderDesc psDesc;
        EBlendState blendState = EBlendState::Opaque;
        EPrimitiveTopology topology = EPrimitiveTopology::TriangleList;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------