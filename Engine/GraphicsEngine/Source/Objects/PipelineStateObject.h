// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/RenderConstants.h"
#include "GraphicsEngine/Resources/IPipelineStateObject.h"
#include "GraphicsEngine/Resources/PipelineStateDesc.h"
#include "Objects/Shader.h"
#include "RHI/RHIMinimal.h"

// Common
#include <string>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    // ------------------------------------------------------------

    struct PipelineStateObject : IPipelineStateObject
    {
        friend class RenderHardwareInterface;

        PipelineStateObject();
        PipelineStateObject(const PipelineStateObject&);
        ~PipelineStateObject();

        void SetDebugName(const std::string& n) const;

        // BEGIN IPipelineStateObject
        const IShader* GetShader(EPipelineStage stage) const override;
        // END IPipelineStateObject

    private:
        ComPtr<RHIVertexLayout> _vertexLayout;

        Shader _vertexShader;
        Shader _pixelShader;

        ComPtr<RHIBlendState> _blendState;

        EPrimitiveTopology _primitiveTopology;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------