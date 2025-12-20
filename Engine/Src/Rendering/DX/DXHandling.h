#pragma once
#include <OstEngine/Common/Math/Color.h>
#include <OstEngine/Rendering/Window.h>
#include <OstEngine/Common/Utility/ByteSize.h>
#include <Src/Rendering/RenderData/EngineInputConstantBuffer.h>

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
            Gigabytes DedicatedVideoMemory = Gigabytes( (Uint64)0u );
            Gigabytes DedicatedSystemMemory = Gigabytes( (Uint64)0u );
            Gigabytes SharedSystemMemory = Gigabytes( (Uint64)0u );
        };

        extern SDXDeviceInfo DeviceInformation;

        extern ID3D11Device* Device;
        extern ID3D11DeviceContext* DeviceContext;

        extern bool Initialize( CWindow& aForWindow );
        extern void ResizeViewport( const Vector2i& aSize );
        extern void Shutdown();

        extern void UpdateEngineWorldData(const SEngineDataRenderInput& aWorldData);

        extern ID3D11VertexShader* CompileVertexShaderFromFile( const std::string& aPath, const std::string& aEntry, ID3DBlob** aOutBlob  );
        extern ID3D11PixelShader* CompilePixelShaderFromFile( const std::string& aPath, const std::string& aEntry );

        extern void BeginRenderFrame( const ost::SColorFlt32& aClearColor );
        extern void PresentRenderFrame();
    } // namespace dx
} // namespace ost