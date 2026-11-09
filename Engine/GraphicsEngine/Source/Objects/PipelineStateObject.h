// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Resources/VertexElement.h"
#include "Objects/Shader.h"
#include "RHI/RHIMinimal.h"

// Common
#include <string>

// ------------------------------------------------------------

namespace ost
{
    // ------------------------------------------------------------

    struct PipelineStateObjectDesc
    {
        List<VertexElement> inputLayout;
        Shader vertexShader;
        Shader pixelShader;
        EBlendState blendState;
        EPrimitiveTopology topology;
    };

    // ------------------------------------------------------------

    struct PipelineStateObject
    {
        PipelineStateObject();
        PipelineStateObject(const PipelineStateObject&);
        ~PipelineStateObject();

        void SetDebugName(const std::string& n) const;

        ComPtr<RHIVertexLayout> _vertexLayout;
        ComPtr<RHIBlendState> _blendState;

        EPrimitiveTopology _primitiveTopology;

        Shader _vertexShader;
        Shader _pixelShader;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------