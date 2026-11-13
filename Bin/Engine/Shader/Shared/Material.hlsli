#ifndef MATERIAL_HLSLI
#define MATERIAL_HLSLI
#include "ShaderCommon.hlsli"

struct SurfaceProperties {
    float2 uv;
    float3 worldPos;
    float3 normal;
    float3 tangent;
    float3 bitangent;
};

struct SurfaceMaterial {
    float3 albedo;
    float3 normal;
    float ao, roughness, metallic;
};

struct PostProcessMaterial {
    float3 color;
};

float SampleR( float2 uv, Texture2D texture, SamplerState textureSampler )
{
    return texture.Sample(textureSampler, uv).r;
}

float2 SampleRG( float2 uv, Texture2D texture, SamplerState textureSampler )
{
    return texture.Sample(textureSampler, uv).rg;
}

float3 SampleRGB( float2 uv, Texture2D texture, SamplerState textureSampler )
{
    return texture.Sample( textureSampler, uv ).rgb;
}

float3 SampleRGBA( float2 uv, Texture2D texture, SamplerState textureSampler )
{
    return texture.Sample(textureSampler, uv).rgba;
}

float3 SampleNormal( float2 uv, float3 normal, float3 tangent, float3 bitangent, Texture2D texture, SamplerState textureSampler )
{
    float2 sampledNormal = SampleRGB( uv, texture, textureSampler ); 
    float3 T = normalize(tangent);
    float3 B = normalize(bitangent);
    float3 N = normalize(normal);
    float3x3 TBN = float3x3(T,B,N);
    return mul(ExtractAndUnpackNormal(sampledNormal), TBN);    
}

void SampleORM( float2 uv, Texture2D texture, SamplerState textureSampler, inout float o, inout float r, inout float m )
{
    float3 orm = SampleRGB(uv, texture, textureSampler);
    o = orm.r;
    r = orm.g;
    m = orm.b;
}

#endif // MATERIAL_HLSLI