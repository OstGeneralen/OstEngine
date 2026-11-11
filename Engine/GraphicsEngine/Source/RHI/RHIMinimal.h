// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <OstTypes.h>
#include <wrl.h>

// ------------------------------------------------------------

// clang-format off
typedef struct ID3D11Device             RHIDevice;
typedef struct ID3D11DeviceContext      RHIDeviceContext;
typedef struct IDXGISwapChain           RHISwapChain;

typedef struct ID3D11Texture2D          RHITexture2D;
typedef struct ID3D11RenderTargetView   RHIRenderTarget;
typedef struct ID3D11ShaderResourceView RHIShaderResource;
typedef struct ID3D11DepthStencilView   RHIDepthStencil;

typedef struct ID3D11SamplerState       RHISampler;
typedef struct ID3D11BlendState         RHIBlendState;
typedef struct ID3D11DepthStencilState  RHIDepthStencilState;

typedef struct ID3D11VertexShader       RHIVertexShader;
typedef struct ID3D11PixelShader        RHIPixelShader;

typedef struct ID3D11InputLayout        RHIVertexLayout;
typedef struct ID3D11Buffer             RHIBuffer;
// clang-format on

// ------------------------------------------------------------

namespace ost
{
    // ------------------------------------------------------------
    // Typedef the annoyingly long namespace for ComPtr away

    template <typename T>
    using ComPtr = Microsoft::WRL::ComPtr<T>;

    // ------------------------------------------------------------

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------