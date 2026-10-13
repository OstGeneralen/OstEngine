#ifndef PBL_SHADER_HLSLI
#define PBL_SHADER_HLSLI
#include "ShaderCore.hlsli"

struct PBRData
{
    float3 albedo;
    float3 normal;
    float3 position;
    float ao, roughness, metallic;
};

float GGXNormalDistribution( float3 normal, float3 halfDir, float roughness )
{
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(normal, halfDir), 0.0f);
    float NdotH2 = NdotH * NdotH;
    float denom = (NdotH2 * (a2-1.0f) + 1.0f);
    return a2 / ( 3.14159f * ( denom * denom));
}

float SchlickGGX(float NdotV, float roughness)
{
    float alpha = roughness * roughness;
    float r = alpha + 1.0f;
    float k = (r * r) / 8.0f;
    return NdotV / (NdotV * (1.0f - k) + k);
}

float GeometrySmith(float3 normal, float3 viewDir, float3 lightDir, float roughness)
{
    float NdotV = max(dot(normal, viewDir), 0.0f);
    float NdotL = max(dot(normal, lightDir), 0.0f);
    return SchlickGGX( NdotV, roughness) * SchlickGGX(NdotL, roughness);
}

float3 FresnelSchlick( float3 f0, float cosTheta )
{
    return f0 + (1.0f - f0) * pow(1.0f - cosTheta, 5.0f);
}

float4 CalculatePBLColor( PBRData data )
{
    const float3 SunColor = Light_SunCol.rgb;

    float3 viewDir = normalize( FrameBuf_ViewLocation.xyz - data.position );
    float3 lightDir = normalize(-Light_SunDir.rgb);
    float3 halfDir = normalize(viewDir + lightDir);

    float3 F0 = float3(0.04f, 0.04f, 0.04f);
    F0 = lerp(F0, data.albedo, data.metallic);

    float NDF = GGXNormalDistribution( data.normal, halfDir, data.roughness );
    float G = GeometrySmith( data.normal, viewDir, lightDir, data.roughness );
    float3 F = FresnelSchlick( F0, max(dot(halfDir, viewDir), 0.0f) );

    float3 numerator = NDF * G * F;
    float denominator = 4.0f * max(dot(data.normal, viewDir), 0.0f) * max(dot(data.normal, lightDir), 0.0f) + 0.0001f;
    float3 specular = numerator / denominator;

    float3 kS = F;
    float3 kD = (1.0f - kS) * (1.0f - data.metallic);

    float NdotL = max(dot(data.normal, lightDir), 0.0f);
    float3 directLight = ((kD * data.albedo / 3.14159f) + specular) * SunColor * NdotL;

    float3 ambientLight = Light_AmbientCol.rgb * data.albedo * data.ao;
    
    float3 color = directLight + ambientLight;
    color = color / (color + 1.0f);

    return float4( color, 1.0f );
    //return float4((data.normal.r + 1.0f) * 0.5f, (data.normal.g + 1.0f) * 0.5f, 0, 1.0f);
    //return float4(data.roughness, data.roughness, data.roughness, 1.0f);
    //return float4(data.metallic, data.metallic, data.metallic,1.0f);
}


#endif