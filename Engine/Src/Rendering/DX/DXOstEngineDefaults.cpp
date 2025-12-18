#include "Src/Rendering/DX/DXOstEngineDefaults.h"

#include "Src/Rendering/DX/DXHandling.h"
#include "Src/Rendering/RenderData/EngineInputConstantBuffer.h"

// ------------------------------------------------------------

void ost::dx::InitializeEngineDefaults()
{
    // Create the Cbuffer that contains the world data (view projection matrix, total time)
    D3D11_BUFFER_DESC bufferDesc;
    ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
    bufferDesc.ByteWidth = sizeof( SEngineDataRenderInput );
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    dx::Device->CreateBuffer( &bufferDesc, nullptr, &WorldDataBuffer );

    // Create the per object buffer
    // Create the perObject cbuffer
    D3D11_BUFFER_DESC perObjectBufferDesc;
    ZeroMemory( &perObjectBufferDesc, sizeof( perObjectBufferDesc ) );
    perObjectBufferDesc.ByteWidth = sizeof( TMatrix4x4<float> );
    perObjectBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    perObjectBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    perObjectBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    dx::Device->CreateBuffer( &perObjectBufferDesc, nullptr, &PerObjectBuffer );

    // Create Sampler State
    D3D11_SAMPLER_DESC samplerDesc;
    ZeroMemory( &samplerDesc, sizeof( samplerDesc ) );
    samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
    samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    samplerDesc.MinLOD = 0;
    samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

    dx::Device->CreateSamplerState( &samplerDesc, &SamplerState );
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------