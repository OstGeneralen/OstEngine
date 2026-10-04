// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RHIMinimal.h"

// DXGI + Dx11
#include <d3d11_1.h>
#include <dxgi.h>

// ------------------------------------------------------------

namespace ost
{

    namespace translate
    {
        // Translate from RHI data format to backend data format
        inline static constexpr DXGI_FORMAT DataFormat(EDataFormat fmt) noexcept
        {
            switch (fmt)
            {
                // clang-format off
            case EDataFormat::RGBA_Float32: return DXGI_FORMAT_R32G32B32A32_FLOAT;
            case EDataFormat::RGBA_Uint8: return DXGI_FORMAT_R8G8B8A8_UINT;
            case EDataFormat::RGBA_Unorm8: return DXGI_FORMAT_R8G8B8A8_UNORM;
            
            case EDataFormat::RGB_Float32: return DXGI_FORMAT_R32G32B32_FLOAT;
            
            case EDataFormat::RG_Float32: return DXGI_FORMAT_R32G32_FLOAT;
            case EDataFormat::RG_Uint8: return DXGI_FORMAT_R8G8_UINT;
            case EDataFormat::RG_Unorm8: return DXGI_FORMAT_R8G8_UNORM;
            
            case EDataFormat::R_Float32: return DXGI_FORMAT_R32_FLOAT;
            case EDataFormat::R_Uint8: return DXGI_FORMAT_R8_UINT;
            case EDataFormat::R_Unorm8: return DXGI_FORMAT_R8_UNORM;

            case EDataFormat::DDS_BC7: return DXGI_FORMAT_BC7_UNORM;
            case EDataFormat::DDS_BC7_SRGB: return DXGI_FORMAT_BC7_UNORM_SRGB;

            case EDataFormat::DepthStencil: return DXGI_FORMAT_D24_UNORM_S8_UINT;
                // clang-format on
            }

            return DXGI_FORMAT_UNKNOWN;
        }

        // Translate from RHI data size to a backend data format
        inline static constexpr DXGI_FORMAT DataSize(EDataSize sz) noexcept
        {
            switch (sz)
            {
                // clang-format off
                case EDataSize::Float4: return DXGI_FORMAT_R32G32B32A32_FLOAT;
                case EDataSize::Float3: return DXGI_FORMAT_R32G32B32_FLOAT;
                case EDataSize::Float2: return DXGI_FORMAT_R32G32_FLOAT;
                case EDataSize::Float: return DXGI_FORMAT_R32_FLOAT;

                case EDataSize::Uint4: return DXGI_FORMAT_R32G32B32A32_UINT;
                case EDataSize::Uint3: return DXGI_FORMAT_R32G32_UINT;
                case EDataSize::Uint2: return DXGI_FORMAT_R32_UINT;
                case EDataSize::Uint: return DXGI_FORMAT_R32_UINT;

                case EDataSize::Byte4: return DXGI_FORMAT_R8G8B8A8_UINT;
                case EDataSize::Byte2: return DXGI_FORMAT_R8G8_UINT;
                case EDataSize::Byte: return DXGI_FORMAT_R8_UINT;
                
                case EDataSize::Unorm4: return DXGI_FORMAT_R8G8B8A8_UNORM;
                case EDataSize::Unorm2: return DXGI_FORMAT_R8G8_UNORM;
                case EDataSize::Unorm: return DXGI_FORMAT_R8_UNORM;
                // clang-format on
            }

            return DXGI_FORMAT_UNKNOWN;
        }

        // Translate from RHI topology to backend topology
        inline static constexpr D3D11_PRIMITIVE_TOPOLOGY PrimitiveTopology(EPrimitiveTopology t) noexcept
        {
            switch (t)
            {
                // clang-format off
                case EPrimitiveTopology::PointList: return D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
                case EPrimitiveTopology::LineList: return D3D11_PRIMITIVE_TOPOLOGY_LINELIST;
                case EPrimitiveTopology::TriangleList: return D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
                // clang-format on
            }

            return D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
        }

    } // namespace translate

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------