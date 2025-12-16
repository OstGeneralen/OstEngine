#include "DXRenderer.h"

#include "../../OstEngineMinimal.h"
#include "../Window.h"

#include <OstEngine/Debug/Logging/Logger.h>
#include <OstEngine/Rendering/DX/DXRenderStateDescriptor.h>
#include <OstEngine/Rendering/DX/DXShaderCompiler.h>
#include <OstEngine/Types.h>

#include <OstEngine/Debug/EngineLogInstances.h>

#include "DXHandling.h"

#include <filesystem>

#include <d3d11.h>
#include <dxgi.h>

// ------------------------------------------------------------
// DX Renderer
// ------------------------------------------------------------

ost::CDXRenderState ost::CDXRenderer::CreateRenderState( const std::string& aRenderStateName )
{
    const std::string osrFileName = aRenderStateName + ".osr";
    const std::string shaderFileName = aRenderStateName + ".hlsl";

    RendererLog.BeginLog( "Create Render State for {}", aRenderStateName );

    if ( std::filesystem::exists( osrFileName ) == false )
    {
        RendererLog.Error( "Cannot create render state from '{}'. Missing .osr file\n\t> Expected: '{}'", osrFileName );
        RendererLog.EndScope();
        return CDXRenderState();
    }
    if ( std::filesystem::exists( shaderFileName ) == false )
    {
        RendererLog.Error( "Cannot create render state from '{}'. Missing .hlsl file\n\t> Expected: '{}'",
                           shaderFileName );
        RendererLog.EndScope();
        return CDXRenderState();
    }

    // Create the render state descriptor
    SDXRenderStateDescriptor desc;
    desc.InitFromFile( osrFileName );
    if ( !desc.IsValid() )
    {
        RendererLog.Error( "Failed to create render state '{}'", osrFileName );
        RendererLog.EndScope();
        return CDXRenderState();
    }

    CDXShaderCompiler vertexCompiler( shaderFileName );
    CDXShaderCompiler pixelCompiler( shaderFileName );

    vertexCompiler.CompileShader( desc.VertexMain, EDxShaderType::Vertex );
    if ( vertexCompiler.HasErrors() )
    {
        RendererLog.EndScope();
        return CDXRenderState();
    }

    pixelCompiler.CompileShader( desc.PixelMain, EDxShaderType::Pixel );
    if ( vertexCompiler.HasErrors() )
    {
        RendererLog.EndScope();
        return CDXRenderState();
    }

    CDXRenderState renderState;
    renderState._renderer = this;
    renderState._vertexShader = vertexCompiler.GetVertexShader();
    renderState._pixelShader = pixelCompiler.GetPixelShader();

    D3D11_INPUT_ELEMENT_DESC* layoutDescs = new D3D11_INPUT_ELEMENT_DESC[desc.NumElements];
    for ( Uint32 i = 0; i < desc.NumElements; ++i )
    {
        Uint32 byteOffset = 0;
        if ( i > 0 )
        {
            byteOffset = layoutDescs[i - 1].AlignedByteOffset + desc.ElementDescs[i - 1].ByteSize;
        }

        layoutDescs[i] = desc.ElementDescs[i].D3DDesc;
        layoutDescs[i].SemanticName = desc.ElementDescs[i].SemanticName.c_str();
        layoutDescs[i].AlignedByteOffset = byteOffset;
    }

    HRESULT r =
        dx::Device->CreateInputLayout( layoutDescs, desc.NumElements, vertexCompiler.GetBlob()->GetBufferPointer(),
                                       vertexCompiler.GetBlob()->GetBufferSize(), &( renderState._inputLayout ) );

    if ( r != S_OK )
    {
        RendererLog.Error( "Failed to create input layout for shader '{}' (Error code: {})", shaderFileName, r );
        renderState._vertexShader->Release();
        renderState._pixelShader->Release();
        RendererLog.EndScope();
        return CDXRenderState();
    }
    RendererLog.EndScope();

    // TODO: Implement creation based on input here
    return std::move( renderState );
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------