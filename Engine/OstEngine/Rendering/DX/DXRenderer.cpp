#include "DXRenderer.h"

#include "../../OstEngineMinimal.h"
#include "../Window.h"

#include <OstEngine/Debug/Logging/Logger.h>
#include <OstEngine/Rendering/DX/DXRenderContext.h>
#include <OstEngine/Rendering/DX/DXRenderStateDescriptor.h>
#include <OstEngine/Rendering/DX/DXShaderCompiler.h>
#include <OstEngine/Types.h>

#include <OstEngine/Debug/EngineLogInstances.h>

#include <filesystem>

#include <d3d11.h>
#include <dxgi.h>

// ------------------------------------------------------------
// DXRenderContext Initialization
// ------------------------------------------------------------

ID3D11Device* ost::dx::Device = nullptr;
ID3D11DeviceContext* ost::dx::DeviceContext = nullptr;

// ------------------------------------------------------------
// DX Renderer
// ------------------------------------------------------------

void ost::CDXRenderer::Initialize( CWindow& aWindow )
{
    DXGI_SWAP_CHAIN_DESC scDesc = {};
    ZeroMemory( &scDesc, sizeof( scDesc ) );
    scDesc.BufferCount = 1;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferDesc.Width = aWindow.GetSize().X;
    scDesc.BufferDesc.Height = aWindow.GetSize().Y;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.SampleDesc.Count = 1;
    scDesc.Windowed = true;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scDesc.OutputWindow = aWindow.GetWindowPointer().Get_AsIs<HWND>();

    D3D_FEATURE_LEVEL featureLevels[] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_11_1,
    };
    const Uint32 numLevels = ARRAYSIZE( featureLevels );

    // clang-format off
    HRESULT result = D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        0,
        featureLevels,
        numLevels,
        D3D11_SDK_VERSION,
        &scDesc,
        &_swapChainPtr,
        &dx::Device,
        NULL,
        &dx::DeviceContext
    );
    // clang-format on

    OST_ASSERT( result == S_OK, "DXRenderer failed to create either device or swapchain" );

    ID3D11Texture2D* backBuffer = nullptr;
    result = _swapChainPtr->GetBuffer( 0, IID_PPV_ARGS( &backBuffer ) );

    OST_ASSERT( result == S_OK, "DXRenderer failed to create back buffer" );

    result = dx::Device->CreateRenderTargetView( backBuffer, NULL, &_renderTargetViewPtr );
    backBuffer->Release();

    OST_ASSERT( result == S_OK, "DXRenderer failed to create Render Target View" );

    dx::DeviceContext->OMSetRenderTargets( 1, &_renderTargetViewPtr, NULL );

    D3D11_VIEWPORT viewport;
    viewport.Width = (Float32)aWindow.GetSize().X;
    viewport.Height = (Float32)aWindow.GetSize().Y;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    dx::DeviceContext->RSSetViewports( 1, &viewport );

    // INIT DEBUG INFO
    IDXGIDevice* dxgiDevice;
    IDXGIAdapter* dxgiAdapter;
    DXGI_ADAPTER_DESC adapterDesc;

    dx::Device->QueryInterface( &dxgiDevice );
    dxgiDevice->GetAdapter( &dxgiAdapter );
    dxgiAdapter->GetDesc( &adapterDesc );
    std::wstring wadapterName = adapterDesc.Description;
    _debugInfo.AdapterName = std::string( wadapterName.begin(), wadapterName.end() );
    _debugInfo.VRAM = adapterDesc.DedicatedVideoMemory / 1024u / 1024u / 1024u;

    RendererLog.BeginConfirm( "D3D11 Initialized Successfully" );
    RendererLog.Log( "Graphics Adapter: {}", _debugInfo.AdapterName );
    RendererLog.Log( "Graphics Memory: {}gb", _debugInfo.VRAM );
    RendererLog.EndScope();
}

// ------------------------------------------------------------

void ost::CDXRenderer::Deinitialize()
{
    _swapChainPtr->Release();
    dx::DeviceContext->Release();
    dx::Device->Release();
}

// ------------------------------------------------------------

void ost::CDXRenderer::Clear( const SColor& aClearColor )
{
    const SColorFlt32 fltColor = aClearColor;
    const Float32 c[4] = { fltColor.R, fltColor.G, fltColor.B, fltColor.A };
    dx::DeviceContext->ClearRenderTargetView( _renderTargetViewPtr, c );
}

// ------------------------------------------------------------

void ost::CDXRenderer::Present()
{
    _swapChainPtr->Present( 1, 0 );
}

// ------------------------------------------------------------

const ost::SDXRendererDebugInfo& ost::CDXRenderer::GetDebugInfo() const
{
    return _debugInfo;
}

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
    for ( Int32 i = 0; i < desc.NumElements; ++i )
    {
        Int32 byteOffset = 0;
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