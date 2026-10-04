#ifndef UNLIT_SURFACE_SHADER_HLSL
#define UNLIT_SURFACE_SHADER_HLSL

#include "EngineMaterial.hlsli"

SurfacePixel VSMain(SurfaceVertex vertex)
{
    float4 worldPosition = mul(vertex.Position, ObjectBuf_Transform);

    MaterialVertexData materialData;
    materialData.WorldPosition = worldPosition;
    materialData.VertexColor = vertex.BaseColor;
    Material_VertexShader( materialData );

    SurfacePixel pixel;
    pixel.BaseColor = materialData.VertexColor;
    pixel.Position = mul( materialData.WorldPosition, FrameBuf_ViewMatrix );
    pixel.Normal = mul(float4(vertex.Normal.xyz, 0), ObjectBuf_Transform);
    pixel.Tangent = mul(float4(vertex.Tangent.xyz, 0), ObjectBuf_Transform);
    pixel.UV = vertex.UV;
    return pixel;
}

float4 PSMain(SurfacePixel pixel ) : SV_Target
{
    float4 finalColor = pixel.BaseColor;

    MaterialPixelData materialData;
    materialData.PixelColor = finalColor;
    Material_PixelShader( materialData );

    return float4(materialData.PixelColor.rgb, 1);
}

#endif