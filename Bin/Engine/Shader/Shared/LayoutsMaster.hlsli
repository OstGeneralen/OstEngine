#ifndef LAYOUTS_MASTER_HLSLI
#define LAYOUTS_MASTER_HLSLI

// ------------------------------------------------------------

struct StaticSurfaceVertex {
    float4 Position : POSITION;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float4 BaseColor : COLOR;
    float2 UV : TEXCOORD;
};

struct StaticSurfaceFragment {
    float4 Position : SV_Position;
    float3 WorldPosition : POSITION;
    float3 ViewPosition : POSITION1;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Bitangent : BINORMAL;
    float4 BaseColor : COLOR;
    float2 UV : TEXCOORD;
};

// ------------------------------------------------------------

struct BlitVertex {
    float4 Position : POSITION;
    float2 UV : TEXCOORD;
};

struct BlitFragment {
    float4 Position : SV_Position;
    float2 UV : TEXCOORD;
};

#endif