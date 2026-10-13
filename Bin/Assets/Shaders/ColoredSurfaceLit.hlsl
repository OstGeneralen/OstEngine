#include "OstMaterial.hlsli"

cbuffer InstanceData : BUFFER_SLOT_MATERIAL_PROPERTIES 
{
    float4 OverrideColor;
    float OverrideStrength;
    float3 PADDING;
};  

void Material_VS( inout MaterialVertexData vertexData )
{

}

void Material_PS(inout MaterialPixelData pixelData)
{
    float3 keepBase = lerp( pixelData.color.rgb, float3(0,0,0), OverrideStrength );
    float3 keepOverride = lerp(float3(0,0,0), OverrideColor.rgb, OverrideStrength );
    float3 finalColor = keepBase + keepOverride;
    pixelData.color = float4(saturate(finalColor), 1);
}