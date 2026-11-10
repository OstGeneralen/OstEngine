#include "../ShaderCommon.hlsli"
#include "../ShaderCore.hlsli"

struct SurfaceData
{
    float3 sceneColor;
    float3 worldNormal;
    float3 worldPos;
    float ao;
    float roughness;
    float metallic;
};

#if MATERIAL_SHADER
#include "MATERIAL"
#else
void MaterialMain( inout SurfaceData s )
{
}
#endif

float4 PSMain( FullscreenPixel pixel )
{
}
