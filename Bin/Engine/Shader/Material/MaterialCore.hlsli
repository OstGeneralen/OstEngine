#ifndef MATERIAL_CORE
#define MATERIAL_CORE

#include "../ShaderCommon.hlsli"

struct MaterialPixelInput
{
    float4 vertexColor;
    float3 normal;
    float3 tangent;
    float3 bitangent;
    float2 uv;
};

struct MaterialSurfaceData
{
    float3 albedo;
    float3 normal;
    float ao;
    float roughness;
    float metallicness;
};

float3 Material_ApplyNormalMap(float2 sampled, MaterialPixelInput frag)
{
    return CalculatePixelNormal( sampled, frag.normal, frag.tangent, frag.bitangent );
}

void MaterialSurface(MaterialPixelInput frag, inout MaterialSurfaceData surface);

#endif