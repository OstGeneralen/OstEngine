#ifndef MATERIAL_HLSLI
#define MATERIAL_HLSLI

struct SurfaceProperties {
    float3 normal;
    float2 uv;
    float3 worldPos;
};

struct SurfaceMaterial {
    float3 albedo;
    float3 normal;
    float ao, roughness, metallic;
};

struct PostProcessMaterial {
    float3 color;
};

#endif // MATERIAL_HLSLI