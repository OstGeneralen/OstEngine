// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
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

    using EPipelineStage_ = Uint32;

    enum EPipelineStage : Uint32
    {
        None = 0,
        EPipelineStage_VS = 1 << 0,
        EPipelineStage_PS = 1 << 1,
    };

    // ------------------------------------------------------------

    enum class EDataFormat
    {
        RGBA_Float32,
        RGBA_Uint8,
        RGBA_Unorm8,

        RGB_Float32,

        RG_Float32,
        RG_Uint8,
        RG_Unorm8,

        R_Float32,
        R_Uint8,
        R_Unorm8,

        DepthStencil,
    };

    // ------------------------------------------------------------

    enum class EDataSize
    {
        Float4,
        Float3,
        Float2,
        Float,

        Uint4,
        Uint3,
        Uint2,
        Uint,

        Byte4,
        Byte2,
        Byte,

        Unorm4,
        Unorm2,
        Unorm,
    };

    // ------------------------------------------------------------

    enum class EPrimitiveTopology
    {
        None = 0,
        PointList,
        LineList,
        TriangleList,
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------