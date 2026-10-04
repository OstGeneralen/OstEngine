#include "EngineMaterial.hlsli"

Texture2D tex_albedo : register(t0);
Texture2D tex_normal : register(t1);
Texture2D tex_ORM : register(t2);

void Material_VertexShader(inout MaterialVertexData vertexData)
{
    // No op
}

void Material_PixelShader(inout MaterialPixelData pixelData)
{
    pixelData.PixelColor = float4(1,1,1,1);
}