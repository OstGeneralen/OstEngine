#include "../ShaderSlots.hlsli"
#include "../ShaderCore.hlsli"
#include "MaterialCore.hlsli"
#include "MaterialInclude"

Texture2D TEX_Albedo : TEXTURE_SLOT_ALBEDO;
Texture2D TEX_Normal : TEXTURE_SLOT_NORMAL;

SurfacePixel VSMain( SurfaceVertex vertex )
{
    MaterialVertexData data;
    data.vertexUV = vertex.UV;
    data.vertexWorldPos = mul(vertex.Position, ObjectBuf_Transform);
    data.vertexColor = vertex.BaseColor;

    //Material_VS( data );

    SurfacePixel output;
    output.BaseColor = data.vertexColor;

    // Calculate TBN
    row_major float3x3 toWorld = ( float3x3 )ObjectBuf_Transform;
    output.Tangent = normalize(mul(vertex.Tangent, toWorld));
    output.Normal = normalize(mul(vertex.Normal, toWorld));
    output.Bitangent = normalize(mul(cross(output.Normal, output.Tangent), toWorld));

    output.Position = mul(data.vertexWorldPos, FrameBuf_ViewMatrix );
    output.UV = data.vertexUV;
    return output;
}


float4 PSMain( SurfacePixel frag ) : SV_Target
{
    float3 albedoColor = TEX_Albedo.Sample(TrilinearWrap, frag.UV).rgb;
    float2 sampleNormal = TEX_Normal.Sample(TrilinearWrap, frag.UV).rg;

    // Unpack
    sampleNormal = (sampleNormal * 2.0f) - 1.0f;

    // Reconstruct
    float3 tangentNormal = float3(sampleNormal.x, sampleNormal.y, 0);
    tangentNormal.z = sqrt( 1.0f - saturate( (sampleNormal.x * sampleNormal.x) + (sampleNormal.y * sampleNormal.y)));

    float3 N = normalize(frag.Normal);
    float3 T = normalize(frag.Tangent);
    float3 B = normalize(frag.Bitangent);
    float3x3 TBN = float3x3(T,B,N);

    float3 pixelNormal = mul(tangentNormal, TBN);

    MaterialPixelData materialData;
    materialData.color = float4(albedoColor.rgb, 1);
    Material_PS(materialData);

    float lightFactor = dot( Light_SunDir.xyz * -1, pixelNormal );
    lightFactor = (lightFactor + 1) * 0.5f;

    float4 finalColor = saturate((materialData.color * lightFactor) + Light_AmbientCol);

    return finalColor;
}