#include "Src/Rendering/DX/DXOstEngineDefaults.h"

#include "Src/Rendering/DX/DXHandling.h"
#include "Src/Rendering/RenderData/EngineInputConstantBuffer.h"

// ------------------------------------------------------------

ID3D11Buffer* ost::dx::WorldDataBuffer = nullptr;
ID3D11Buffer* ost::dx::PerObjectBuffer = nullptr;
ID3D11SamplerState* ost::dx::SamplerState = nullptr;

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

ID3D11InputLayout* ost::dx::CreateInputLayout( void* aBufPtr, Uint64 aBufSize )
{
    // Create the input layout
    D3D11_INPUT_ELEMENT_DESC inputDesc[3];
    ZeroMemory( &inputDesc, sizeof( inputDesc ) );

    // Vector3 position
    inputDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    inputDesc[0].SemanticName = "POSITION";
    inputDesc[0].AlignedByteOffset = 0;
    inputDesc[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;

    // Vector3 normal
    inputDesc[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    inputDesc[1].SemanticName = "NORMAL";
    inputDesc[1].AlignedByteOffset = sizeof(Float32) * 3;
    inputDesc[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;


    // Vector2 uv
    inputDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
    inputDesc[2].SemanticName = "TEXCOORD";
    inputDesc[2].AlignedByteOffset = sizeof(Float32) * 6;
    inputDesc[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;


    ID3D11InputLayout* il;
    dx::Device->CreateInputLayout( inputDesc, 3, aBufPtr, aBufSize, &il );
    return il;
}

// ------------------------------------------------------------

void ost::dx::UseEngineDefaults()
{
    ID3D11Buffer* cbuffs[2] = { WorldDataBuffer, PerObjectBuffer };
    DeviceContext->VSSetConstantBuffers( 0, 2, cbuffs );
    DeviceContext->VSSetSamplers( 0, 1, &SamplerState );

    DeviceContext->PSGetConstantBuffers( 0, 2, cbuffs );
    DeviceContext->PSSetSamplers( 0, 1, &SamplerState );
}

// ------------------------------------------------------------


void ost::dx::UpdatePerObjectBuffer( const TMatrix4x4<float>& aModelMat )
{
    D3D11_MAPPED_SUBRESOURCE mapped;
    dx::DeviceContext->Map( PerObjectBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped );
    const Uint64 matSize = sizeof( TMatrix4x4<float> );
    memcpy_s( mapped.pData, matSize, &aModelMat, matSize );
    dx::DeviceContext->Unmap( PerObjectBuffer, 0 );
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------