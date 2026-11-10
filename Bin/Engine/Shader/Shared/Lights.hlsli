#ifndef LIGHTS_HLSLI
#define LIGHTS_HLSLI

struct DirectionalLight {
    float3 direction;
    float3 color;
};

struct PointLight {
    float3 worldPosition;
    float radius;
    float3 color;
};

struct SpotLight {
    float3 worldPosition;
    float3 direction;
    float range;
    float innerRadius;
    float outerRadius;
    float3 color;
};

#endif // LIGHT_HLSLI