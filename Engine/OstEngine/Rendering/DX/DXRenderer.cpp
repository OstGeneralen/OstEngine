#include "DXRenderer.h"

#include "../Window.h"

#include <OstEngine/Types.h>
#include <cassert>
#include <d3d11.h>
#include <dxgi.h>

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

    if ( FAILED( result ) )
    {
        // early out here
        assert( false );
    }

    ID3D11Texture2D* backBuffer = nullptr;
    result = _swapChainPtr->GetBuffer( 0, IID_PPV_ARGS( &backBuffer ) );
    if ( FAILED( result ) )
    {
        assert( false );
    }

    result = _devicePtr->CreateRenderTargetView( backBuffer, NULL, &_renderTargetViewPtr );
    backBuffer->Release();
    if ( FAILED( result ) )
    {
        assert( false );
    }

    _deviceContextPtr->OMSetRenderTargets( 1, &_renderTargetViewPtr, NULL );

    D3D11_VIEWPORT viewport;
    viewport.Width = (Float32)aWindow.GetSize().X;
    viewport.Height = (Float32)aWindow.GetSize().Y;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    _deviceContextPtr->RSSetViewports( 1, &viewport );
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
// ------------------------------------------------------------
// ------------------------------------------------------------