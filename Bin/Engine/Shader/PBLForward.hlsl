#include "ShaderSlots.hlsli"
#include "ShaderCore.hlsli"
#include "ShaderCommon.hlsli"
#include "PBLShader.hlsli"
#include "Material/MaterialCore.hlsli"
#include "MaterialInclude"

SurfacePixel VSMain(SurfaceVertex vertex) {
    float4 worldPosition = mul(vertex.Position, ObjectBuf_Transform);

    SurfacePixel output;
    output.BaseColor = vertex.BaseColor;

    // Calculate TBN
    VSTangentSpace ts = VSCalculateTangentSpace(ObjectBuf_Transform, vertex.Normal, vertex.Tangent);
    output.Tangent = ts.tangent;
    output.Normal = ts.normal;
    output.Bitangent = ts.bitangent;

    output.Position = mul(worldPosition, FrameBuf_ViewProjection);
    output.WorldPosition = worldPosition;
    output.UV = vertex.UV;

    return output;
}

float4 PSMain(SurfacePixel frag) : SV_Target {
    // Sample PLB textures
    float3 albedoColor = TEX_Albedo.Sample(TrilinearWrap, frag.UV).rgb;
    float2 sampleNormal = TEX_Normal.Sample(TrilinearWrap, frag.UV).rg;
    float3 ORM = TEX_Orm.Sample(TrilinearWrap, frag.UV).rgb;

    // Calculate Tangent Normal
    float3 pixelNormal = CalculatePixelNormal(sampleNormal, frag.Normal, frag.Tangent, frag.Bitangent);

    // Calculate the PBL lit pixel
    PBRData pblData;
    pblData.albedo = albedoColor;
    pblData.normal = pixelNormal;
    pblData.position =  frag.WorldPosition.rgb;
    pblData.ao = ORM.r;
    pblData.roughness = max(0.001f, ORM.g);
    pblData.metallic = max(0.001f, ORM.b);
    float4 litColor = CalculatePBLColor(pblData);

    MaterialPixelData materialData;
    materialData.albedo = albedoColor;
    materialData.color = litColor;
    materialData.normal = pixelNormal;
    materialData.uv = frag.UV;
    Material_PS(materialData);

    const float gamma = 1.9f;
    float3 gammaCorrected = float3(pow(materialData.color.r, 1.0f / gamma), pow(materialData.color.g, 1.0f / gamma), pow(materialData.color.b, 1.0f / gamma));

    return float4(gammaCorrected, 1);
    //return float4(sampleNormal.r, sampleNormal.g, 1, 1);
    //return float4( (frag.Normal.r + 1.0f) * 0.5f, (frag.Normal.g + 1.0f) * 0.5f, 1.0f, 1.0f );
}