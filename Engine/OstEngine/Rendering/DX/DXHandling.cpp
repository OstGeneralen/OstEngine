#include "DXHandling.h"

#include "../../Debug/Logging/LogInstance.h"

#include <Windows.h>

// ------------------------------------------------------------

ost::log::CLogInstance DXLog( "D3D11" );

// ------------------------------------------------------------

namespace internal
{
    IDXGISwapChain* SwapChain = nullptr;
    ID3D11RenderTargetView* RenderTargetView = nullptr;

    bool InitDeviceAndSwapChain( Int32 w, Int32 h, HWND hwnd );
    bool InitRenderTargetViewAndBackbuffer();
    bool InitViewport( Int32 w, Int32 h );

    bool CleanupReturnFalse();

} // namespace internal

ost::dx::SDXDeviceInfo ost::dx::DeviceInformation = {};
ID3D11Device* ost::dx::Device = nullptr;
ID3D11DeviceContext* ost::dx::DeviceContext = nullptr;

// ------------------------------------------------------------

bool ost::dx::Initialize( ost::CWindow& aForWindow )
{
    const Int32 windowWidth = aForWindow.GetSize().X;
    const Int32 windowHeight = aForWindow.GetSize().Y;
    HWND windowHandle = aForWindow.GetWindowPointer().Get_AsIs<HWND>();

    if ( !internal::InitDeviceAndSwapChain( windowWidth, windowHeight, windowHandle ) )
    {
        return internal::CleanupReturnFalse();
    }

    if ( !internal::InitRenderTargetViewAndBackbuffer() )
    {
        return internal::CleanupReturnFalse();
    }

    if ( !internal::InitViewport( windowWidth, windowHeight ) )
    {
        return internal::CleanupReturnFalse();
    }

    // Assign the debug/device info
    IDXGIDevice* dxgiDevice;
    IDXGIAdapter* dxgiAdapter;
    DXGI_ADAPTER_DESC adapterDesc;

    ost::dx::Device->QueryInterface( &dxgiDevice );
    dxgiDevice->GetAdapter( &dxgiAdapter );
    dxgiAdapter->GetDesc( &adapterDesc );
    std::wstring adapterNameW = adapterDesc.Description;

    {
        using namespace ost::dx;
        const Uint64 dedicatedVideoMemory = static_cast<Uint64>( adapterDesc.DedicatedVideoMemory );
        const Uint64 dedicatedSystemMemory = static_cast<Uint64>( adapterDesc.DedicatedSystemMemory );
        const Uint64 sharedSystemMemory = static_cast<Uint64>( adapterDesc.SharedSystemMemory );

        DeviceInformation.AdapterName = std::string( adapterNameW.begin(), adapterNameW.end() );
        DeviceInformation.DedicatedVideoMemory = ByteSize::Bytes( dedicatedVideoMemory );
        DeviceInformation.DedicatedSystemMemory = ByteSize::Bytes( dedicatedSystemMemory );
        DeviceInformation.SharedSystemMemory = ByteSize::Bytes( sharedSystemMemory );
    }

    DXLog.BeginConfirm( "Successfully initialized D3D11" );
    DXLog.Log( "Adapter: {}", DeviceInformation.AdapterName );
    DXLog.Log( "Dedicated VRAM: {}gb", DeviceInformation.DedicatedVideoMemory.Num );
    DXLog.Log( "Dedicated Sys: {}gb", DeviceInformation.DedicatedSystemMemory.Num );
    DXLog.Log( "Shared Sys: {}gb", DeviceInformation.SharedSystemMemory.Num );
    DXLog.EndScope();
    
    return true;
}

// ------------------------------------------------------------

void ost::dx::Shutdown()
{
    internal::CleanupReturnFalse();
}

// ------------------------------------------------------------

bool internal::InitDeviceAndSwapChain( Int32 w, Int32 h, HWND hwnd )
{
    DXGI_SWAP_CHAIN_DESC scDesc = {};
    ZeroMemory( &scDesc, sizeof( scDesc ) );
    scDesc.BufferCount = 1;
    scDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scDesc.BufferDesc.Width = w;
    scDesc.BufferDesc.Height = h;
    scDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scDesc.SampleDesc.Count = 1;
    scDesc.Windowed = true;
    scDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scDesc.OutputWindow = hwnd;

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
        &internal::SwapChain,
        &ost::dx::Device,
        NULL,
        &ost::dx::DeviceContext
    );
    // clang-format on
    if ( result != S_OK )
    {
        DXLog.Error( "Failed to create d3d11 device and/or swapchain" );
        return false;
    }
    return true;
}

// ------------------------------------------------------------

void ost::dx::ResizeViewport( const ost::Vector2i& aSize )
{
    D3D11_VIEWPORT viewport;
    viewport.Width = (Float32)aSize.X;
    viewport.Height = (Float32)aSize.Y;
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;

    ost::dx::DeviceContext->RSSetViewports( 1, &viewport );
}

// ------------------------------------------------------------

void ost::dx::BeginRenderFrame( const ost::SColorFlt32& aClearColor )
{
    const Float32 c[4] = { aClearColor.R, aClearColor.G, aClearColor.B, aClearColor.A };
    ost::dx::DeviceContext->ClearRenderTargetView( internal::RenderTargetView, c );
}

// ------------------------------------------------------------

void ost::dx::PresentRenderFrame()
{
    internal::SwapChain->Present(1, 0);
}

// ------------------------------------------------------------

bool internal::InitRenderTargetViewAndBackbuffer()
{
    ID3D11Texture2D* backBuffer = nullptr;
    HRESULT result = internal::SwapChain->GetBuffer( 0, IID_PPV_ARGS( &backBuffer ) );

    if ( result != S_OK )
    {
        DXLog.Error( "Failed to access buffer from swapchain" );
        return false;
    }

    result = ost::dx::Device->CreateRenderTargetView( backBuffer, NULL, &internal::RenderTargetView );
    backBuffer->Release();

    if ( result != S_OK )
    {
        DXLog.Error( "Failed to create render target view" );
        return false;
    }

    // Todo: Might want to add a depth stencil here
    ost::dx::DeviceContext->OMSetRenderTargets( 1, &internal::RenderTargetView, NULL );

    return true;
}

// ------------------------------------------------------------

bool internal::InitViewport( Int32 w, Int32 h )
{
    ost::dx::ResizeViewport( { w, h } );
    return true;
}

// ------------------------------------------------------------

bool internal::CleanupReturnFalse()
{
    if ( internal::RenderTargetView )
    {
        internal::RenderTargetView->Release();
    }
    if ( ost::dx::DeviceContext )
    {
        ost::dx::DeviceContext->Release();
    }
    if ( internal::SwapChain )
    {
        internal::SwapChain->Release();
    }
    if ( ost::dx::Device )
    {
        ost::dx::Device->Release();
    }
    return false;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------