#include "../ShaderSlots.hlsli"
#include "../ShaderCore.hlsli"
#include "../ShaderCommon.hlsli"
#include "../PBLShader.hlsli"
#include "MaterialCore.hlsli"
#include "MaterialInclude"

Texture2D TEX_Albedo : TEXTURE_SLOT_ALBEDO;
Texture2D TEX_Normal : TEXTURE_SLOT_NORMAL;
Texture2D TEX_Orm : TEXTURE_SLOT_ORM;

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
    output.Bitangent = normalize(cross(output.Normal, output.Tangent));

    output.Position = mul(data.vertexWorldPos, FrameBuf_ViewProjection );
    output.WorldPosition = data.vertexWorldPos;
    output.UV = data.vertexUV;
    return output;
}


float4 PSMain( SurfacePixel frag ) : SV_Target
{
    // Sample PLB textures
    float3 albedoColor = TEX_Albedo.Sample(TrilinearWrap, frag.UV).rgb;
    float2 sampleNormal = TEX_Normal.Sample(TrilinearWrap, frag.UV).rg;
    float3 ORM = TEX_Orm.Sample(TrilinearWrap, frag.UV).rgb;

    // Calculate Tangent Normal
    float3 tangentNormal = ExtractAndUnpackNormal( sampleNormal );

    float3 N = normalize(frag.Normal);
    float3 T = normalize(frag.Tangent);
    float3 B = normalize(frag.Bitangent);
    float3x3 TBN = float3x3(T,B,N);

    float3 pixelNormal = mul(tangentNormal, TBN);

    // Calculate the PBL lit pixel
    PBRData pblData;
    pblData.albedo = albedoColor;
    pblData.normal = pixelNormal;
    pblData.position =  frag.WorldPosition.rgb;
    pblData.ao = ORM.r;
    pblData.roughness = max(0.001f, ORM.g);
    pblData.metallic = max(0.001f, ORM.b);
    float4 litColor = CalculatePBLColor( pblData );

    MaterialPixelData materialData;
    materialData.color = litColor;
    Material_PS(materialData);

    const float gamma = 1.9f;
    float3 gammaCorrected = float3( pow(materialData.color.r, 1.0f / gamma), pow(materialData.color.g, 1.0f / gamma), pow(materialData.color.b, 1.0f / gamma) );

    return float4(gammaCorrected, 1);
    //return float4(sampleNormal.r, sampleNormal.g, 1, 1);
    //return float4( (frag.Normal.r + 1.0f) * 0.5f, (frag.Normal.g + 1.0f) * 0.5f, 1.0f, 1.0f );
}