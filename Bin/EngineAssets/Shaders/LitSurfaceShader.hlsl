#ifndef LIT_SURFACE_SHADER_HLSL
#define LIT_SURFACE_SHADER_HLSL

#include "ShaderCore.hlsli"
#include "EngineMaterial.hlsli"

SurfacePixel VSMain( SurfaceVertex vertex )
{
    float4 worldPos = mul(vertex.Position, ObjectBuf_Transform);
    float3 worldNormal = mul(float4(vertex.Normal.rgb, 0), ObjectBuf_Transform);
    float3 worldTangent = mul(float4(vertex.Tangent.rgb, 0), ObjectBuf_Transform);

    MaterialVertexData matData;
    matData.WorldPosition = worldPos;
    matData.VertexColor = vertex.BaseColor;
    Material_VertexShader( matData );

    SurfacePixel pixel;
    pixel.Position =  mul(matData.WorldPosition, FrameBuf_ViewMatrix);
    pixel.Normal = worldNormal;
    pixel.Tangent = worldTangent;
    pixel.BaseColor = matData.VertexColor;
    pixel.UV = vertex.BaseColor;

    return pixel;
}

float4 PSMain(SurfacePixel pixel) : SV_TARGET
{

    MaterialPixelData matData;
    matData.PixelColor = pixel.BaseColor;
    Material_PixelShader( matData );

    float envLightIntensity = saturate(dot( pixel.Normal, Light_SunDir.xyz * -1.0f ));
    float4 finalColor = matData.PixelColor * saturate(( Light_SunCol * envLightIntensity ) + (Light_AmbientCol));

    return float4(matData.PixelColor.rgb, 1);
}

#endif