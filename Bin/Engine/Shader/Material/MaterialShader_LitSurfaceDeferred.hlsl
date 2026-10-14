#include "../ShaderSlots.hlsli"
#include "../ShaderCore.hlsli"
#include "../ShaderCommon.hlsli"
#include "../PBLShader.hlsli"
#include "MaterialCore.hlsli"
#include "MaterialInclude"

Texture2D TEX_Albedo : TEXTURE_SLOT_ALBEDO;
Texture2D TEX_Normal : TEXTURE_SLOT_NORMAL;
Texture2D TEX_Orm : TEXTURE_SLOT_ORM;
Texture2D TEX_Pos : TEXTURE_SLOT_DEFERRED_POS;

SurfacePixel VSMain_Color( SurfaceVertex vertex )
{
    MaterialVertexData data;
    data.vertexUV = vertex.UV;
    data.vertexWorldPos = mul(vertex.Position, ObjectBuf_Transform);
    data.vertexColor = vertex.BaseColor;

    //Material_VS( data );

    SurfacePixel output;
    output.BaseColor = data.vertexColor;

    // Calculate TBN
    VSTangentSpace ts = VSCalculateTangentSpace( ObjectBuf_Transform, vertex.Normal, vertex.Tangent );
    output.Tangent = ts.tangent;
    output.Normal = ts.normal;
    output.Bitangent = ts.bitangent;

    output.Position = mul(data.vertexWorldPos, FrameBuf_ViewProjection );
    output.WorldPosition = data.vertexWorldPos;
    output.UV = data.vertexUV;
    return output;
}


DeferredOutput_Color PSMain_Color( SurfacePixel frag )
{
    // Sample PLB textures
    float3 albedoColor = TEX_Albedo.Sample(TrilinearWrap, frag.UV).rgb;
    float2 sampleNormal = TEX_Normal.Sample(TrilinearWrap, frag.UV).rg;
    float3 ORM = TEX_Orm.Sample(TrilinearWrap, frag.UV).rgb;

    // Calculate Tangent Normal
    float3 pixelNormal = CalculatePixelNormal(sampleNormal, frag.Normal, frag.Tangent, frag.Bitangent);


    DeferredOutput_Color output;
    output.Albedo = float4(albedoColor.rgb, 1);
    output.Normal = float4(pixelNormal.rgb, 1);
    output.ORM = float4(ORM.rgb, 1);
    output.WorldPos = frag.WorldPosition.xyz;
    
    return output;
    //return float4(sampleNormal.r, sampleNormal.g, 1, 1);
    //return float4( (frag.Normal.r + 1.0f) * 0.5f, (frag.Normal.g + 1.0f) * 0.5f, 1.0f, 1.0f );
}

FullscreenPixel VSMain_Light( FullscreenVertex vertex )
{
    FullscreenPixel px;
    px.Position = vertex.Position;
    px.UV = vertex.UV;
    return px;
}

float4 PSMain_Light( FullscreenPixel frag )
{
    float3 albedo = TEX_Albedo.Sample(PointWrap, frag.UV).rgb;
    float3 normal = TEX_Normal.Sample(PointWrap, frag.UV).rgb;
    float3 ORM = TEX_Orm.Sample(PointWrap, frag.UV).rgb;
    float3 worldPos = TEX_Pos.Sample( PointWrap, frag.UV ).rgb;

    PBRData pblData;
    pblData.albedo = albedo;
    pblData.normal = normal;
    pblData.position = worldPos;
    pblData.ao = ORM.r;
    pblData.roughness = max(0.001f, ORM.g);
    pblData.metallic = max(0.001f, ORM.b);
    float4 litColor = CalculatePBLColor( pblData );

    const float gamma = 1.9f;
    float3 gammaCorrected = float3( pow(litColor.r, 1.0f / gamma), pow(litColor.g, 1.0f / gamma), pow(litColor.b, 1.0f / gamma) );

    return float4(gammaCorrected, 1);    

}