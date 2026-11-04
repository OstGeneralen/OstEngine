// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Resources/IPipelineStateObject.h"
#include "Objects/Shader.h"
#include "RHI/RHIMinimal.h"

// Common
#include <string>

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