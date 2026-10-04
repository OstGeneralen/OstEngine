#ifndef MATERIAL_HLSLI
#define MATERIAL_HLSLI
#include "ShaderCore.hlsli"

struct MaterialVertexData
{
    float4 WorldPosition;
    float4 VertexColor;
};

struct MaterialPixelData
{
    float4 PixelColor;
};

void Material_VertexShader( inout MaterialVertexData param );
void Material_PixelShader( inout MaterialPixelData param );

#endif