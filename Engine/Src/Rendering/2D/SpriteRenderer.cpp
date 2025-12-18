#include "OstEngine/Rendering/2D/SpriteRenderer.h"

#include "OstEngine/Rendering/RenderData/Vertex.h"
#include "Src/Rendering/DX/DXHandling.h"
#include "Src/Rendering/DX/DXOstEngineDefaults.h"

// ------------------------------------------------------------

void ost::CSpriteRenderer::Initialize()
{
    D3D11_BUFFER_DESC vertBufDesc;
    ZeroMemory( &vertBufDesc, sizeof( vertBufDesc ) );
    vertBufDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertBufDesc.StructureByteStride = sizeof( SDefaltVertex );
    vertBufDesc.ByteWidth = sizeof( SDefaltVertex ) * 6;

    // clang-format off
    SDefaltVertex quadVerts[6] =
    { 
        {{ -1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 0.0f }},
        {{ 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }},
        {{ -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }},

        {{ 1.0f, 1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 0.0f }},
        {{ 1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 1.0f, 1.0f }},
        {{ -1.0f, -1.0f, 0.0f }, { 0.0f, 0.0f, -1.0f }, { 0.0f, 1.0f }},
    };

    // clang-format on

    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory( &initData, sizeof( initData ) );
    initData.pSysMem = quadVerts;

    ID3D11Buffer* buffer;
    dx::Device->CreateBuffer( &vertBufDesc, &initData, &buffer );
    _spriteQuadVertexBuffer = buffer;

    _spriteShaderBundle.InitFromFile( "Engine/Shaders/OstEngineSpriteShader.hlsl" );
}

// ------------------------------------------------------------

void ost::CSpriteRenderer::Draw( const SSprite& aSprite )
{
    _commands.emplace_back( aSprite );
}

// ------------------------------------------------------------

void ost::CSpriteRenderer::Render()
{
    dx::DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    dx::UseEngineDefaults();
    _spriteShaderBundle.BeginUse();

    // Bind the quad vertex buffer
    ID3D11Buffer* vertexBuffer = _spriteQuadVertexBuffer.Get<ID3D11Buffer*>();
    UINT stride = static_cast<UINT>( sizeof( SDefaltVertex ) );
    UINT offset = 0u;
    dx::DeviceContext->IASetVertexBuffers( 0, 1, &vertexBuffer, &stride, &offset );

    // Now draw all the sprites
    for ( const auto& cmd : _commands )
    {
        ID3D11ShaderResourceView* textureResView = cmd.TextureResource.Get<ID3D11ShaderResourceView*>();
        dx::DeviceContext->PSSetShaderResources( 0, 1, &textureResView );
        dx::UpdatePerObjectBuffer( cmd.ModelMatrix );
        dx::DeviceContext->Draw( 6, 0 );
    }

    _commands.clear();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------