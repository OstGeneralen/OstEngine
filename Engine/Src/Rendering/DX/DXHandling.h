#pragma once
#include <OstEngine/Math/Color.h>
#include <OstEngine/Rendering/Window.h>
#include <OstEngine/Utility/ByteSize.h>

#include <string>

#include <d3d11.h>
#include <dxgi.h>

namespace ost
{
    namespace dx
    {
        struct SDXDeviceInfo
        {
            std::string AdapterName = "";
            ByteSize::Gigabytes DedicatedVideoMemory = ByteSize::Gigabytes( (Uint64)0u );
            ByteSize::Gigabytes DedicatedSystemMemory = ByteSize::Gigabytes( (Uint64)0u );
            ByteSize::Gigabytes SharedSystemMemory = ByteSize::Gigabytes( (Uint64)0u );
        };

        extern SDXDeviceInfo DeviceInformation;

        extern ID3D11Device* Device;
        extern ID3D11DeviceContext* DeviceContext;

        extern bool Initialize( CWindow& aForWindow );
        extern void ResizeViewport( const Vector2i& aSize );
        extern void Shutdown();

        extern ID3D11VertexShader* CompileVertexShaderFromFile( const std::string& aPath, const std::string& aEntry, void** outShaderBuffer, Uint64& outBufferSize  );
        extern ID3D11PixelShader* CompilePixelShaderFromFile( const std::string& aPath, const std::string& aEntry );

        extern void BeginRenderFrame( const ost::SColorFlt32& aClearColor );
        extern void PresentRenderFrame();
    } // namespace dx
} // namespace ost