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

struct DirectionalLight
{
    float3 direction;
    float3 color;
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

float3 CalculatePBLLight( float3 dirToLight, float3 color, PBRData surface )
{
    float3 viewDir = normalize( FrameBuf_ViewLocation.xyz - surface.position );
    float3 lightDir = normalize(dirToLight);
    float3 halfDir = normalize(viewDir + lightDir);

    float3 F0 = float3(0.04f, 0.04f, 0.04f);
    F0 = lerp(F0, surface.albedo, surface.metallic);

    float NDF = GGXNormalDistribution( surface.normal, halfDir, surface.roughness );
    float G = GeometrySmith( surface.normal, viewDir, lightDir, surface.roughness );
    float3 F = FresnelSchlick( F0, max(dot(halfDir, viewDir), 0.0f) );

    float3 numerator = NDF * G * F;
    float denominator = 4.0f * max(dot(surface.normal, viewDir), 0.0f) * max(dot(surface.normal, lightDir), 0.0f) + 0.0001f;
    float3 specular = numerator / denominator;

    float3 kS = F;
    float3 kD = (1.0f - kS) * (1.0f - surface.metallic);

    float NdotL = max(dot(surface.normal, lightDir), 0.0f);
    float3 directLight = ((kD * surface.albedo / 3.14159f) + specular) * color * NdotL;

    return directLight;
}

//float4 CalculatePBLColor( float3 color, float3 direction, PBRData data )
//{
//    float3 viewDir = normalize( FrameBuf_ViewLocation.xyz - data.position );
//    float3 lightDir = normalize(-direction);
//    float3 halfDir = normalize(viewDir + lightDir);
//
//    float3 F0 = float3(0.04f, 0.04f, 0.04f);
//    F0 = lerp(F0, data.albedo, data.metallic);
//
//    float NDF = GGXNormalDistribution( data.normal, halfDir, data.roughness );
//    float G = GeometrySmith( data.normal, viewDir, lightDir, data.roughness );
//    float3 F = FresnelSchlick( F0, max(dot(halfDir, viewDir), 0.0f) );
//
//    float3 numerator = NDF * G * F;
//    float denominator = 4.0f * max(dot(data.normal, viewDir), 0.0f) * max(dot(data.normal, lightDir), 0.0f) + 0.0001f;
//    float3 specular = numerator / denominator;
//
//    float3 kS = F;
//    float3 kD = (1.0f - kS) * (1.0f - data.metallic);
//
//    float NdotL = max(dot(data.normal, lightDir), 0.0f);
//    float3 directLight = ((kD * data.albedo / 3.14159f) + specular) * color * NdotL;
//
//    //float3 ambientLight = Light_AmbientCol.rgb * data.albedo * data.ao;
//    //
//    //float3 color = directLight + ambientLight;
//    color = color / (color + 1.0f);
//
//    return float4( color, 1.0f );
//}

float3 CalculatePBLDirectionalLight( float3 direction, float3 color, PBRData surface )
{
    float3 dirToLight = normalize(-direction);
    return CalculatePBLLight( dirToLight, color, surface );
}

float3 CalculatePBLPointLight( float3 color, float3 position, float radius, PBRData surface )
{
    float3 toLight = position - surface.position;
    
    float3 dirToLight = normalize(toLight);
    float distanceToLight = length(toLight);

    float3 finalColor = CalculatePBLLight(dirToLight, color, surface);

    float attenuation = saturate(1.0f - (distanceToLight / radius));
    finalColor *= (attenuation * attenuation);

    return finalColor;
}


#endif