#define MATERIAL_SHADER
#include "Material.hlsli"

void Material_VertexShader(inout MaterialVertexData params)
{
    params.VertexColor = float4(1,1,1,1);
}

void Material_PixelShader(inout MaterialPixelData params)
{
    // No-op We've set the colour in the vertex shader :)
}