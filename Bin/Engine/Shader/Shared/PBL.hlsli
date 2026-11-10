#ifndef PBL_HLSLI
#define PBL_HLSLI
#include "Lights.hlsli"

struct PBLData {
    float3 viewLocation;
    float3 albedo;
    float3 normal;
    float3 position;
    float ao, roughness, metallic;
};

float GGXNormalDistribution(float3 normal, float3 halfDir, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH = max(dot(normal, halfDir), 0.0f);
    float NdotH2 = NdotH * NdotH;
    float denom = (NdotH2 * (a2-1.0f) + 1.0f);
    return a2 / (3.14159f * (denom * denom));
}

float SchlickGGX(float NdotV, float roughness) {
    float alpha = roughness * roughness;
    float r = alpha + 1.0f;
    float k = (r * r) / 8.0f;
    return NdotV / (NdotV * (1.0f - k) + k);
}

float GeometrySmith(float3 normal, float3 viewDir, float3 lightDir, float roughness) {
    float NdotV = max(dot(normal, viewDir), 0.0f);
    float NdotL = max(dot(normal, lightDir), 0.0f);
    return SchlickGGX(NdotV, roughness) * SchlickGGX(NdotL, roughness);
}

float3 FresnelSchlick(float3 f0, float cosTheta) {
    return f0 + (1.0f - f0) * pow(1.0f - cosTheta, 5.0f);
}

float3 CalculatePBLLight(float3 dirToLight, float3 color, PBLData data) {
    float3 viewDir = normalize(data.viewLocation - data.position);
    float3 lightDir = normalize(dirToLight);
    float3 halfDir = normalize(viewDir + lightDir);

    float3 F0 = float3(0.04f, 0.04f, 0.04f);
    F0 = lerp(F0, data.albedo, data.metallic);

    float NDF = GGXNormalDistribution(data.normal, halfDir, data.roughness);
    float G = GeometrySmith(data.normal, viewDir, lightDir, data.roughness);
    float3 F = FresnelSchlick(F0, max(dot(halfDir, viewDir), 0.0f));

    float3 numerator = NDF * G * F;
    float denominator = 4.0f * max(dot(data.normal, viewDir), 0.0f) * max(dot(data.normal, lightDir), 0.0f) + 0.0001f;
    float3 specular = numerator / denominator;

    float3 kS = F;
    float3 kD = (1.0f - kS) * (1.0f - data.metallic);

    float NdotL = max(dot(data.normal, lightDir), 0.0f);
    float3 directLight = ((kD * data.albedo / 3.14159f) + specular) * color * NdotL;

    return directLight;
}

float3 CalculatePBLDirectionalLight(DirectionalLight light, PBLData surface) {
    float3 dirToLight = normalize(-light.direction);
    return CalculatePBLLight(dirToLight, light.color, surface);
}

float3 CalculatePBLPointLight(PointLight light, PBLData surface) {
    float3 toLight = light.worldPosition - surface.position;

    float3 dirToLight = normalize(toLight);
    float distanceToLight = length(toLight);

    float3 finalColor = CalculatePBLLight(dirToLight, light.color, surface);

    float attenuation = saturate(1.0f - (distanceToLight / light.radius));
    finalColor *= (attenuation * attenuation);

    return finalColor;
}

float3 CalculatePBLSpotLight(SpotLight light, PBLData surface) {
    const float cosInner = cos(light.innerRadius);
    const float cosOuter = cos(light.outerRadius);

    float3 lightToSurface = normalize(surface.position - light.worldPosition);
    float spotFactor = saturate(dot(lightToSurface, light.direction));
    float spotAttenuation = smoothstep(cosOuter, cosInner, spotFactor);

    PointLight pl;
    pl.color = light.color;
    pl.radius = light.range;
    pl.worldPosition = light.worldPosition;
    float3 finalColor = CalculatePBLPointLight(pl, surface);
    finalColor *= (spotAttenuation * spotAttenuation);

    return finalColor;
}

#endif // PBL_HLSLI