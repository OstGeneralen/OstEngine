#include "ShaderSlots.hlsli"
#include "ShaderCore.hlsli"
#include "ShaderCommon.hlsli"
#include "PBLShader.hlsli"
#include "Material/MaterialCore.hlsli"
#include "MaterialInclude"

// ------------------------------------------------------------

float4 PSMain_Fullscreen(FullscreenPixel frag) : SV_Target {
    MaterialPixelInput materialInput;
    materialInput.uv = frag.UV;

    MaterialSurfaceData surfaceData;
    MaterialSurface(materialInput, surfaceData);

    return float4(surfaceData.albedo.rgb, 1);
}

// ------------------------------------------------------------

float4 PSMain_LitSurface_Forward(SurfacePixel frag) : SV_Target {
    MaterialPixelInput materialInput;
    materialInput.normal = frag.Normal;
    materialInput.tangent = frag.Tangent;
    materialInput.bitangent = frag.Bitangent;
    materialInput.uv = frag.UV;
    materialInput.vertexColor = frag.BaseColor;

    MaterialSurfaceData surfaceData;
    MaterialSurface(materialInput, surfaceData);

    PBRData pblData;
    pblData.albedo = surfaceData.albedo;
    pblData.normal = surfaceData.normal;
    pblData.ao = surfaceData.ao;
    pblData.roughness = max(surfaceData.roughness, 0.0001f);
    pblData.metallic = max(surfaceData.metallicness, 0.0001f);
    pblData.position = frag.WorldPosition;

    float4 litColor = CalculatePBLColor(pblData);

    const float gamma = 1.9f;
    return float4(GammaCorrectOutput(litColor.rgb, gamma), 1);
}

// ------------------------------------------------------------

GBuffer PSMain_Surface_Geometry(SurfacePixel frag) {
    MaterialPixelInput materialInput;
    materialInput.normal = frag.Normal;
    materialInput.tangent = frag.Tangent;
    materialInput.bitangent = frag.Bitangent;
    materialInput.uv = frag.UV;
    materialInput.vertexColor = frag.BaseColor;

    MaterialSurfaceData surfaceData;
    MaterialSurface(materialInput, surfaceData);

    GBuffer gbuf;
    gbuf.Albedo = float4(surfaceData.albedo, 1);
    gbuf.Normal = float4(PackNormal(surfaceData.normal), 1);
    gbuf.ORM = float4(float3(surfaceData.ao, surfaceData.roughness, surfaceData.metallicness), 1);
    return gbuf;
}

// ------------------------------------------------------------

Texture2D GBuffer_Albedo : register(t0);
Texture2D GBuffer_Normal : register(t1);
Texture2D GBuffer_ORM : register(t2);
Texture2D GBuffer_Depth : register(t3);

float4 PSMain_Surface_Lit(FullscreenPixel frag)  : SV_Target {
    float3 albedo = GBuffer_Albedo.Sample(PointWrap, frag.UV).rgb;
    float3 normal = UnpackNormal(GBuffer_Normal.Sample(PointWrap, frag.UV).rgb);
    float3 ORM = GBuffer_ORM.Sample(PointWrap, frag.UV).rgb;
    float depth = GBuffer_Depth.Sample(PointWrap, frag.UV).r;

    float3 worldPos = ReconstructWorldPosition(frag.UV, depth, FrameBuf_InverseViewProjection);

    PBRData pblData;
    pblData.albedo = albedo;
    pblData.normal = normalize(normal);
    pblData.ao = ORM.r;
    pblData.roughness = max(ORM.g, 0.0001f);
    pblData.metallic = max(ORM.b, 0.0001f);
    pblData.position = worldPos;
    float4 litColor = CalculatePBLColor(pblData);

    return float4(GammaCorrectOutput(litColor.rgb, 1.9f), 1);
    //return float4(litColor.rgb, 1);
}