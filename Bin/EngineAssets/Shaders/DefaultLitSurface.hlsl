#include "EngineMaterial.hlsli"

void Material_VertexShader(inout MaterialVertexData vertexData)
{
    // No op
}

void Material_PixelShader(inout MaterialPixelData pixelData)
{
    pixelData.PixelColor = float4(1,1,1,1);
}