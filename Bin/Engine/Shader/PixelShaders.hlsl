#include "ShaderCore.hlsli"
#include "ShaderCommon.hlsli"
#include "PBLShader.hlsli"

// ------------------------------------------------------------

float3 CalculateLights(PBRData surface) {
    float3 totalLight = float3(0,0,0);

    for(uint i = 0; i < LightBuffer_numLights; i++) {
        float3 thisLight = float3(0,0,0);
        switch(LightBuffer_lights[i].type) {
            case 0:
            thisLight = CalculatePBLDirectionalLight(LightBuffer_lights[i].direction, LightBuffer_lights[i].color.rgb, surface);
            break;
            case 1:
            thisLight = CalculatePBLSpotLight(LightBuffer_lights[i].color.rgb, LightBuffer_lights[i].position, LightBuffer_lights[i].direction, LightBuffer_lights[i].outerRadius, LightBuffer_lights[i].radius, LightBuffer_lights[i].range, surface);
            break;
            case 2:
            thisLight = CalculatePBLPointLight(LightBuffer_lights[i].color.rgb, LightBuffer_lights[i].position, LightBuffer_lights[i].radius, surface);
            break;
        }
        totalLight = totalLight + thisLight;
    }

    return saturate(totalLight);
}

// ------------------------------------------------------------

Texture2D Texture_Albedo : register(t0);
Texture2D Texture_Normal : register(t1);
Texture2D Texture_ORM : register(t2);

GBuffer PSMain_Surface_Geometry(SurfacePixel frag) {
    float3 albedo = Texture_Albedo.Sample(TrilinearWrap, frag.UV).rgb;
    float2 normal = Texture_Normal.Sample(TrilinearWrap, frag.UV).rg;
    float3 orm = Texture_ORM.Sample(TrilinearWrap, frag.UV).rgb;

    float3 pixelNormal = CalculatePixelNormal(normal, frag.Normal, frag.Tangent, frag.Bitangent);

    GBuffer gbuf;
    gbuf.Albedo = float4(albedo, 1);
    gbuf.Normal = float4(PackNormal(pixelNormal), 1);
    gbuf.ORM = float4(orm, 1);
    return gbuf;
}

// ------------------------------------------------------------

Texture2D Blit_Colour : register(t0);

float4 PSMain_Blit(FullscreenPixel frag) : SV_Target {
    float4 color = Blit_Colour.Sample(PointWrap, frag.UV);
    color.a = 1;
    return color;
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

    float3 litColor = CalculateLights(pblData);

    return float4(GammaCorrectOutput(litColor.rgb, 1.9f), 1);
    //return float4(litColor.rgb, 1);
}