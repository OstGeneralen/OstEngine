#include "Shared/ShaderCommon.hlsli"
#include "Shared/PBL.hlsli"
#include "Shared/Resources.hlsli"
#include "Shared/LayoutsMaster.hlsli"

// ------------------------------------------------------------

float3 CalculateLights(PBLData data) {
    float3 totalLight = float3(0,0,0);

    for(uint i = 0; i < LightBuffer_numLights; i++) {
        LightData light = LightBuffer_lights[i];

        float3 illumination = float3(0);

        switch(light.type) {
            case 0: {
                DirectionalLight dl;
                dl.color = light.color;
                dl.direction = light.direction;
                illumination = CalculatePBLDirectionalLight(dl, data);
                break;
            }
            case 1: {
                SpotLight sl;
                sl.color = light.color;
                sl.direction = light.direction;
                sl.worldPosition = light.position;
                sl.innerRadius = light.radius;
                sl.outerRadius = light.outerRadius;
                sl.range = light.range;
                illumination = CalculatePBLSpotLight(sl, data);
                break;
            }
            case 2: {
                PointLight pl;
                pl.color = light.color;
                pl.radius = light.radius;
                pl.worldPosition = light.position;
                illumination = CalculatePBLPointLight(pl, data);
                break;
            }
        }
        totalLight = totalLight + illumination;
    }

    return saturate(totalLight);
}

// ------------------------------------------------------------

Texture2D gbuffer_albedo : register(t0);
Texture2D gbuffer_normal : register(t1);
Texture2D gbuffer_orm : register(t2);
Texture2D gbuffer_depth : register(t3);

float4 PSMain(BlitFragment frag) : SV_Target {
    PBLData pblData;
    pblData.albedo = gbuffer_albedo.Sample(PointWrap, frag.UV).rgb;
    pblData.normal = UnpackNormal(gbuffer_normal.Sample(PointWrap, frag.UV).rgb);
    pblData.viewLocation = FrameBuf_ViewLocation;
    pblData.position = ReconstructWorldPosition(frag.UV, gbuffer_depth.Sample(PointWrap, frag.UV).r, FrameBuf_InverseViewProjection);

    float3 orm = gbuffer_orm.Sample(PointWrap, frag.UV).rgb;
    pblData.ao = orm.r;
    pblData.roughness = orm.g;
    pblData.metallic = orm.b;

    float3 finalColor = pblData.albedo;

    finalColor = CalculateLights(pblData);

    return float4(GammaCorrectOutput(finalColor.rgb, 1.9f), 1);
}

// ------------------------------------------------------------