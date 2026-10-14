#ifndef SHADER_CORE_HLSLI
#define SHADER_CORE_HLSLI

// Shader Slot Definitions
#define TEXTURE_SLOT_ALBEDO register(t0)
#define TEXTURE_SLOT_NORMAL register(t1)
#define TEXTURE_SLOT_ORM register(t2)
#define MATERIAL_TEXTURE_SLOT_1 register(t3)
#define MATERIAL_TEXTURE_SLOT_2 register(t4)
#define MATERIAL_TEXTURE_SLOT_3 register(t5)
#define MATERIAL_TEXTURE_SLOT_4 register(t6)
#define MATERIAL_TEXTURE_SLOT_5 register(t7)

#define TEXTURE_SLOT_DEFERRED_POS register(t8)

#define SAMPLER_SLOT_POINT_WRAP register(s0)
#define SAMPLER_SLOT_BILINEAR_WRAP register(s1)
#define SAMPLER_SLOT_TRILINEAR_WRAP register(s2)
#define SAMPLER_SLOT_POINT_CLAMP register(s3)
#define SAMPLER_SLOT_BILINEAR_CLAMP register(s4)
#define SAMPLER_SLOT_TRILINEAR_CLAMP register(s5)

#define BUFFER_SLOT_MATERIAL_PROPERTIES register(b0)

#define BUFFER_SLOT_FRAME register(b10)
#define BUFFER_SLOT_OBJECT register(b11)
#define BUFFER_SLOT_LIGHT register(b12)
#define BUFFER_SLOT_ANIMATION register(b13)

// Samplers
SamplerState PointWrap : SAMPLER_SLOT_POINT_WRAP;
SamplerState PointClamp : SAMPLER_SLOT_POINT_CLAMP;

SamplerState BilinearWrap : SAMPLER_SLOT_BILINEAR_WRAP;
SamplerState BilinearClamp : SAMPLER_SLOT_BILINEAR_CLAMP;

SamplerState TrilinearWrap : SAMPLER_SLOT_TRILINEAR_WRAP;
SamplerState TrilinearClamp : SAMPLER_SLOT_TRILINEAR_CLAMP;

// Buffers
cbuffer FrameBuffer : BUFFER_SLOT_FRAME
{
    row_major float4x4 FrameBuf_ViewProjection;
    row_major float4x4 FrameBuf_ViewInverse;
    float4 FrameBuf_ViewLocation;
};

cbuffer ObjectBuffer : BUFFER_SLOT_OBJECT
{
    row_major float4x4 ObjectBuf_Transform;
};

cbuffer LightBuffer : BUFFER_SLOT_LIGHT
{
    float4 Light_SunDir;
    float4 Light_SunCol;
    float4 Light_AmbientCol;
};

// Deferred Rendering output
struct DeferredOutput_Color
{
    float4 Albedo : SV_Target0; 
    float4 Normal : SV_Target1;
    float4 ORM : SV_Target2;
    float3 WorldPos : SV_Target3;
};

// Shader Layouts
struct FullscreenVertex
{
    float4 Position : POSITION;
    float2 UV : TEXCOORD;
};

struct FullscreenPixel
{
    float4 Position : SV_Position;
    float2 UV : TEXCOORD;
}; 

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
    float3 WorldPosition : POSITION;
    float3 Normal : NORMAL;
    float3 Tangent : TANGENT;
    float3 Bitangent : BINORMAL;
    float4 BaseColor : COLOR;
    float2 UV : TEXCOORD;
};

#endif