#ifndef RESOURCES_HLSLI
#define RESOURCES_HLSLI

// ------------------------------------------------------------
// Samplers
// ------------------------------------------------------------

SamplerState PointWrap : register(s0);
SamplerState PointClamp : register(s3);

SamplerState BilinearWrap : register(s1);
SamplerState BilinearClamp : register(s4);

SamplerState TrilinearWrap : register(s2);
SamplerState TrilinearClamp : register(s5);

// ------------------------------------------------------------
// Buffers
// ------------------------------------------------------------

cbuffer FrameBuffer : register(b10) {
    row_major float4x4 FrameBuf_ViewProjection;
    row_major float4x4 FrameBuf_InverseViewProjection;
    row_major float4x4 FrameBuf_ViewInverse;
    float4 FrameBuf_ViewLocation;
};

// ------------------------------------------------------------

cbuffer ObjectBuffer : register(b11) {
    row_major float4x4 ObjectBuf_Transform;
};

// ------------------------------------------------------------

struct LightData {
    float4 color;
    float3 position;
    uint type;
    float3 direction;
    float radius;
    float outerRadius;
    float range;
    float2 PADDING;
};

cbuffer LightBuffer : register(b12) {
    LightData LightBuffer_lights[8];
    uint LightBuffer_numLights;
    float3 LBPADDING0;
};

// ------------------------------------------------------------

struct GBuffer {
    float4 albedo : SV_Target0;
    float4 normal : SV_Target1;
    float4 orm : SV_Target2;
};

// ------------------------------------------------------------

#endif // RESOURCES_HLSLI