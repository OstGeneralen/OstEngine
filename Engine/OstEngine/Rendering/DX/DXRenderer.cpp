#include "DXRenderer.h"

#include "../../OstEngineMinimal.h"
#include "../Window.h"

#include <OstEngine/Debug/Logging/Logger.h>
#include <OstEngine/Rendering/DX/DXRenderStateDescriptor.h>
#include <OstEngine/Types.h>

#include <filesystem>

#include <d3d11.h>
#include <dxgi.h>

#include <OstEngine/Rendering/DX/DXShaderCompiler.h>

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
        &_devicePtr,
        NULL,
        &_deviceContextPtr
    );
    // clang-format on

    OST_ASSERT( result == S_OK, "DXRenderer failed to create either device or swapchain" );

    ID3D11Texture2D* backBuffer = nullptr;
    result = _swapChainPtr->GetBuffer( 0, IID_PPV_ARGS( &backBuffer ) );

    OST_ASSERT( result == S_OK, "DXRenderer failed to create back buffer" );

    result = _devicePtr->CreateRenderTargetView( backBuffer, NULL, &_renderTargetViewPtr );
    backBuffer->Release();

    OST_ASSERT( result == S_OK, "DXRenderer failed to create Render Target View" );

    _deviceContextPtr->OMSetRenderTargets( 1, &_renderTargetViewPtr, NULL );

    D3D11_VIEWPORT viewport;
    viewport.Width = (Float32)aWindow.GetSize().X;
    viewport.Height = (Float32)aWindow.GetSize().Y;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    _deviceContextPtr->RSSetViewports( 1, &viewport );

    // INIT DEBUG INFO
    IDXGIDevice* dxgiDevice;
    IDXGIAdapter* dxgiAdapter;
    DXGI_ADAPTER_DESC adapterDesc;

    _devicePtr->QueryInterface( &dxgiDevice );
    dxgiDevice->GetAdapter( &dxgiAdapter );
    dxgiAdapter->GetDesc( &adapterDesc );
    std::wstring wadapterName = adapterDesc.Description;
    _debugInfo.AdapterName = std::string( wadapterName.begin(), wadapterName.end() );
    _debugInfo.VRAM = adapterDesc.DedicatedVideoMemory / 1024u / 1024u / 1024u;

    Logging::Confirm( "d3d11 initialized" );
    Logging::Log( "Graphics Adapter: {}", _debugInfo.AdapterName );
    Logging::Log( "Graphics Memory: {}gb", _debugInfo.VRAM );
}

// ------------------------------------------------------------

void ost::CDXRenderer::Deinitialize()
{
    _swapChainPtr->Release();
    _deviceContextPtr->Release();
    _devicePtr->Release();
}

// ------------------------------------------------------------

void ost::CDXRenderer::Clear( const SColor& aClearColor )
{
    const SColorFlt32 fltColor = aClearColor.ToFlt32Color();
    const Float32 c[4] = { fltColor.R, fltColor.G, fltColor.B, fltColor.A };
    _deviceContextPtr->ClearRenderTargetView( _renderTargetViewPtr, c );
}

// ------------------------------------------------------------

void ost::CDXRenderer::Present()
{
    _swapChainPtr->Present( 1, 0 );
}

// ------------------------------------------------------------

ID3D11Device* ost::CDXRenderer::GetDevicePointer()
{
    return _devicePtr;
}

// ------------------------------------------------------------

ID3D11DeviceContext* ost::CDXRenderer::GetDeviceContextPointer()
{
    return _deviceContextPtr;
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

    if ( std::filesystem::exists( osrFileName ) == false )
    {
        Logging::Error( "Cannot create render state from '{}'. Missing .osr file\n\t> Expected: '{}'", osrFileName );
        return CDXRenderState();
    }
    if ( std::filesystem::exists( shaderFileName ) == false )
    {
        Logging::Error( "Cannot create render state from '{}'. Missing .hlsl file\n\t> Expected: '{}'", shaderFileName );
        return CDXRenderState();
    }

    // Create the render state descriptor
    SDXRenderStateDescriptor desc;
    desc.InitFromFile( osrFileName );
    if ( !desc.IsValid() )
    {
        Logging::Error( "Failed to create render state '{}'", osrFileName );
        return CDXRenderState();
    }

    CDXShaderCompiler vertexCompiler( shaderFileName );
    CDXShaderCompiler pixelCompiler( shaderFileName );

    vertexCompiler.CompileShader( desc.VertexMain, EDxShaderType::Vertex, _devicePtr );
    if (vertexCompiler.HasErrors())
    {
        Logging::Error( "Failed to compile shader: '{}'", shaderFileName );
        Logging::Error( "{}", vertexCompiler.GetErrorString() );
        return CDXRenderState();
    }

    pixelCompiler.CompileShader( desc.PixelMain, EDxShaderType::Pixel, _devicePtr );
    if ( vertexCompiler.HasErrors() )
    {
        Logging::Error( "Failed to compile shader: '{}'", shaderFileName );
        Logging::Error( "{}", pixelCompiler.GetErrorString() );
        return CDXRenderState();
    }

    CDXRenderState renderState;
    renderState._renderer = this;
    renderState._vertexShader = vertexCompiler.GetVertexShader();
    renderState._pixelShader = pixelCompiler.GetPixelShader();

    
    D3D11_INPUT_ELEMENT_DESC* layoutDescs = new D3D11_INPUT_ELEMENT_DESC[desc.NumElements];
    for (Int32 i = 0; i < desc.NumElements; ++i)
    {
        layoutDescs[i] = desc.ElementDescs[i].D3DDesc;
        layoutDescs[i].SemanticName = desc.ElementDescs[i].SemanticName.c_str();
    }

    HRESULT r =  _devicePtr->CreateInputLayout( layoutDescs, desc.NumElements, vertexCompiler.GetBlob()->GetBufferPointer(),
                                   vertexCompiler.GetBlob()->GetBufferSize(), &( renderState._inputLayout ) );

    if (r != S_OK)
    {
        Logging::Error( "Failed to create input layout for shader '{}' (Error code: {})", shaderFileName, r );
        renderState._vertexShader->Release();
        renderState._pixelShader->Release();
        return CDXRenderState();
    }

    Logging::Confirm( "Successfully compiled shader '{}'", shaderFileName );

    // TODO: Implement creation based on input here
    return std::move(renderState);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------