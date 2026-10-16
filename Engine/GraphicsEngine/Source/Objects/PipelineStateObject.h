// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/RenderConstants.h"
#include "RHI/RHIMinimal.h"

// Common
#include <string>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    // ------------------------------------------------------------

    struct VertexElement
    {
        std::string semanticName;
        EDataSize dataSize;
    };

    struct PipelineStateObjectDesc
    {
        struct ShaderByteCode
        {
            void* pBytecode;
            SizeType bytecodeSize;
        };

        ShaderByteCode vertexShader;
        ShaderByteCode pixelShader;

        EBlendState blendState = EBlendState::Opaque;
        List<VertexElement> vertexLayout;

        EPrimitiveTopology primitiveTopology;
    };

    // ------------------------------------------------------------

    struct PipelineStateObject
    {
        friend class RenderHardwareInterface;

        PipelineStateObject();
        PipelineStateObject(const PipelineStateObject&);
        ~PipelineStateObject();

        void SetDebugName(const std::string& n) const;

    private:
        ComPtr<RHIVertexLayout> _vertexLayout;

        ComPtr<RHIVertexShader> _vertexShader;
        ComPtr<RHIPixelShader> _pixelShader;

        ComPtr<RHIBlendState> _blendState;

        EPrimitiveTopology _primitiveTopology;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------