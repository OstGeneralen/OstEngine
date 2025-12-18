#include "Src/Rendering/OstEngineDefaultRenderer.h"

#include "Src/Rendering/DX/DXHandling.h"
#include "Src/Rendering/RenderData/EngineInputConstantBuffer.h"

namespace
{
    const std::string shaderPath = "Engine/Shaders/DefaultShader.hlsl";
} // namespace

void ost::CDefaultRenderer::Initialize()
{
    ID3DBlob* shaderBlob;
    _vertexShader = dx::CompileVertexShaderFromFile( ::shaderPath, "vsMain", &shaderBlob);
    _pixelShader = dx::CompilePixelShaderFromFile( ::shaderPath, "psMain" );

    // Create the input layout
    D3D11_INPUT_ELEMENT_DESC inputDesc[3];
    ZeroMemory( &inputDesc, sizeof( inputDesc ) );

    // Vector3 position
    inputDesc[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    inputDesc[0].SemanticName = "POSITION";
    inputDesc[0].AlignedByteOffset = 0;

    // Vector3 normal
    inputDesc[1].Format = DXGI_FORMAT_R32G32B32_FLOAT;
    inputDesc[1].SemanticName = "NORMAL";
    inputDesc[1].AlignedByteOffset = 12;

    // Vector2 uv
    inputDesc[2].Format = DXGI_FORMAT_R32G32_FLOAT;
    inputDesc[2].SemanticName = "TEXCOORD";
    inputDesc[2].AlignedByteOffset = 24;

    dx::Device->CreateInputLayout( inputDesc, 3, shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(),
                                   &_inputLayout );

    // Create the engineInput cbuffer
    D3D11_BUFFER_DESC bufferDesc;
    ZeroMemory( &bufferDesc, sizeof( bufferDesc ) );
    bufferDesc.ByteWidth = sizeof( SEngineDataRenderInput );
    bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    dx::Device->CreateBuffer( &bufferDesc, nullptr, &_engineInputBuffer );

    // Create the perObject cbuffer
    D3D11_BUFFER_DESC perObjectBufferDesc;
    ZeroMemory( &perObjectBufferDesc, sizeof( perObjectBufferDesc ) );
    perObjectBufferDesc.ByteWidth = sizeof( TMatrix4x4<float> );
    perObjectBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
    perObjectBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    perObjectBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    dx::Device->CreateBuffer( &perObjectBufferDesc, nullptr, &_perObjectBuffer );

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

    dx::Device->CreateSamplerState( &samplerDesc, &_samplerState );

    // Create the quad vertex buffer
    SDefaltVertex quadVerts[4] = { { { -1.0f, -1.f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.f, 0.f } },
                                   { { 1.0f, -1.f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.f, 0.f } },
                                   { { -1.0f, 1.f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.f, 1.f } },
                                   { { 1.0f, 1.f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.f, 1.f } } };

    D3D11_BUFFER_DESC vBufDesc;
    ZeroMemory( &vBufDesc, sizeof( vBufDesc ) );
    vBufDesc.ByteWidth = sizeof( SDefaltVertex ) * 4;
    vBufDesc.CPUAccessFlags = DXGI_CPU_ACCESS_NONE;
    vBufDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vBufDesc.StructureByteStride = sizeof( SDefaltVertex );

    D3D11_SUBRESOURCE_DATA resData;
    ZeroMemory( &resData, sizeof( resData ) );
    resData.pSysMem = &quadVerts;

    dx::Device->CreateBuffer( &vBufDesc, &resData, &_quadVertexBuffer );
}

void ost::CDefaultRenderer::UpdateEngineInput( const SEngineDataRenderInput& aUpdatedData )
{
    D3D11_MAPPED_SUBRESOURCE mapped;
    dx::DeviceContext->Map( _engineInputBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped );
    memcpy_s( mapped.pData, sizeof( SEngineDataRenderInput ), &aUpdatedData, sizeof( SEngineDataRenderInput ) );
    dx::DeviceContext->Unmap( _engineInputBuffer, 0 );
}

void ost::CDefaultRenderer::PerformRender()
{
    // Set all shared resource between all sprites
    
    // Input Assembler (Layout and topology)
    dx::DeviceContext->IASetInputLayout( _inputLayout );
    dx::DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    // Vertex stage (shader, input buffer and sampler)
    dx::DeviceContext->VSSetShader( _vertexShader, nullptr, 0 );
    dx::DeviceContext->VSSetConstantBuffers( 0, 1, &_engineInputBuffer );
    dx::DeviceContext->VSSetSamplers( 0, 1, &_samplerState );

    // Pixel stage (shader)
    dx::DeviceContext->PSSetShader( _pixelShader, nullptr, 0 );

    // Vertex Buffer
    const Uint32 stride = static_cast<Uint32>( sizeof( SDefaltVertex ) );
    const Uint32 offset = 0;
    dx::DeviceContext->IASetVertexBuffers( 0, 1, &_quadVertexBuffer, &stride, &offset );

    // Render all draw calls
    for ( const auto& cmd : _pendingDraws )
    {
        // Update the per object buffer for model matrix
        // (The per object buffer and the texture resource)
        D3D11_MAPPED_SUBRESOURCE instanceData;
        dx::DeviceContext->Map( _perObjectBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &instanceData );
        memcpy_s( instanceData.pData, sizeof( TMatrix4x4<float> ), &( cmd.ModelMatrix ), sizeof( TMatrix4x4<float> ) );
        dx::DeviceContext->Unmap( _perObjectBuffer, 0 );

        dx::DeviceContext->VSSetShaderResources( 0, 1, &( cmd.TextureResource ) );

        // Draw the quad (we know this is a quad)
        dx::DeviceContext->Draw( 4, 0 );
    }
}