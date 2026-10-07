#pragma once
#ifndef SHADER_CORE_HLSLI
#define SHADER_CORE_HLSLI

#include "ShaderSlots.hlsli"

// Samplers
SamplerState PointWrap : SAMPLER_SLOT_POINT_WRAP;
SamplerState PointClamp : SAMPLER_SLOT_POINT_CLAMP;

SamplerState BilinearWrap : SAMPLER_SLOT_BILINEAR_WRAP;
SamplerState BilinearClamp : SAMPLER_SLOT_BILINEAR_CLAMP;

SamplerState TrilinearWrap : SAMPLER_SLOT_BILINEAR_WRAP;
SamplerState TrilinearClamp : SAMPLER_SLOT_BILINEAR_CLAMP;

// Buffers
cbuffer FrameBuffer : BUFFER_SLOT_FRAME
{
    row_major float4x4 FrameBuf_ViewMatrix;
    row_major float4x4 FrameBuf_ViewMatrixInv;
};

cbuffer ObjectBuffer : BUFFER_SLOT_OBJECT
{
    row_major float4x4 ObjectBuf_Transform;
};

struct PointLightData
{
    float4 color;
    float3 pos;
    float range;
};

struct SpotLightData
{
    float4 color;
    float3 pos;
    float range;
    float angle;
    float3 PADDING;
};

cbuffer LightBuffer : BUFFER_SLOT_LIGHT
{
    float4 Light_SunDir;
    float4 Light_SunCol;
    float4 Light_AmbientCol;
};

cbuffer AnimBuffer : BUFFER_SLOT_ANIMATION
{
    row_major float4x4 AnimBuf_Bones[128];
};

// Shader Layouts
struct SurfaceVertex
{
    float4 Position : POSITION;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float4 BaseColor : COLOR;
    float2 UV : TEXCOORD;
};

struct SurfacePixel
{
    float4 Position : SV_Position;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float4 BaseColor : COLOR;
    float2 UV : TEXCOORD;
};

#endif