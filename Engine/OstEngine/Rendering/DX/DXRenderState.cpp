#include "DXRenderState.h"

#include "OstEngine/OstEngineMinimal.h"

#include <OstEngine/Rendering/DX/DXRenderer.h>
#include <OstEngine/Rendering/DX/DXHandling.h>

// ------------------------------------------------------------

ost::CDXRenderState::CDXRenderState()
    : _renderer{ nullptr }
    , _vertexShader{ nullptr }
    , _pixelShader{ nullptr }
    , _inputLayout{ nullptr }
{
}

// ------------------------------------------------------------

ost::CDXRenderState::CDXRenderState( CDXRenderState&& aOther ) noexcept
    : _renderer{ aOther._renderer }
    , _vertexShader{ aOther._vertexShader }
    , _pixelShader{ aOther._pixelShader }
    , _inputLayout{ aOther._inputLayout }
{
    aOther._renderer = nullptr;
    aOther._pixelShader = nullptr;
    aOther._vertexShader = nullptr;
    aOther._inputLayout = nullptr;
}


// ------------------------------------------------------------

ost::CDXRenderState::~CDXRenderState()
{
}

// ------------------------------------------------------------

ost::CDXRenderState& ost::CDXRenderState::operator=( CDXRenderState&& aOther ) noexcept
{
    OST_ASSERT( _renderer == nullptr, "Must not already be initialized when moved into" );

    std::swap( aOther._renderer, _renderer );
    std::swap( aOther._vertexShader, _vertexShader );
    std::swap( aOther._pixelShader, _pixelShader );
    std::swap( aOther._inputLayout, _inputLayout );
    return *this;
}

// ------------------------------------------------------------

void ost::CDXRenderState::BindConstantBuffer( const CDXConstantBuffer& aBuffer )
{
    ID3D11Buffer* buffer = aBuffer.GetDXResource();
    dx::DeviceContext->VSSetConstantBuffers( 0, 1, &buffer );
}

// ------------------------------------------------------------

void ost::CDXRenderState::Bind()
{
    OST_ASSERT( _renderer != nullptr, "Cannot bind a Render Pipeline with no valid renderer" );
    OST_ASSERT( _vertexShader != nullptr, "Cannot bind a Render Pipeline with no valid vertex shader" );
    OST_ASSERT( _pixelShader != nullptr, "Cannot bind a Render Pipeline with no valid pixel shader" );
    OST_ASSERT( _inputLayout != nullptr, "Cannot bind a Render Pipeline with no valid input layout" );

    // Set Input Layout
    dx::DeviceContext->IASetInputLayout( _inputLayout );

    // Bind Shaders
    dx::DeviceContext->VSSetShader( _vertexShader, NULL, 0 );
    dx::DeviceContext->PSSetShader( _pixelShader, NULL, 0 );
}

// ------------------------------------------------------------

void ost::CDXRenderState::Unbind()
{
    OST_ASSERT( _renderer != nullptr, "Cannot unbind a Render Pipeline with no valid renderer" );

    // Set Input Layout
    dx::DeviceContext->IASetInputLayout( NULL );

    // Bind Shaders
    dx::DeviceContext->VSSetShader( NULL, NULL, 0 );
    dx::DeviceContext->PSSetShader( NULL, NULL, 0 );
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------