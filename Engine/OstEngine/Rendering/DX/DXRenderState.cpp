#include "DXRenderState.h"

#include "OstEngine/OstEngineMinimal.h"

#include <OstEngine/Rendering/DX/DXRenderer.h>

#include <d3d11.h>
#include <dxgi.h>

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

void ost::CDXRenderState::Bind()
{
    OST_ASSERT( _renderer != nullptr, "Cannot bind a Render Pipeline with no valid renderer" );
    OST_ASSERT( _vertexShader != nullptr, "Cannot bind a Render Pipeline with no valid vertex shader" );
    OST_ASSERT( _pixelShader != nullptr, "Cannot bind a Render Pipeline with no valid pixel shader" );
    OST_ASSERT( _inputLayout != nullptr, "Cannot bind a Render Pipeline with no valid input layout" );

    ID3D11DeviceContext* context = _renderer->GetDeviceContextPointer();

    // Set Input Layout
    context->IASetInputLayout( _inputLayout );

    // Bind Shaders
    context->VSSetShader( _vertexShader, NULL, 0 );
    context->PSSetShader( _pixelShader, NULL, 0 );
}

// ------------------------------------------------------------

void ost::CDXRenderState::Unbind()
{
    OST_ASSERT( _renderer != nullptr, "Cannot unbind a Render Pipeline with no valid renderer" );

    ID3D11DeviceContext* context = _renderer->GetDeviceContextPointer();

    // Set Input Layout
    context->IASetInputLayout( NULL );

    // Bind Shaders
    context->VSSetShader( NULL, NULL, 0 );
    context->PSSetShader( NULL, NULL, 0 );
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------