#include "OstMaterial.hlsli"

cbuffer MaterialData : BUFFER_SLOT_MATERIAL_PROPERTIES
{
    uint OUTPUT_default;
    uint OUTPUT_unlit;
    uint OUTPUT_normals;
    uint OUTPUT_uv;
}; 

void Material_VS( inout MaterialVertexData vertexData )
{

}

void Material_PS(inout MaterialPixelData pixelData)
{  
    float3 outputColor = float3(1,1,1);

    if(OUTPUT_default == 1)
    {
        outputColor = pixelData.color.rgb;
    }
    else if(OUTPUT_unlit ==  1)
    {
        outputColor = pixelData.albedo;
    }
    else if(OUTPUT_normals == 1)
    {
        outputColor = (pixelData.normal + float3(1,1,1)) * 0.5f;
    }
    else if(OUTPUT_uv == 1)
    {
        outputColor = float3( pixelData.uv.r, pixelData.uv.g, 0 );
    }

    pixelData.color = float4(outputColor.rgb, 1);
}