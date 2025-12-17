// Constant Buffer Slot 0 is always the view projection matrices
cbuffer engineInput : register(b0)
{
    float4x4 viewProjectionMatrix;
    float totalTime;
    float3 padding; // Pad to 16-byte
} 

float4x4 modelMatrix : register(b1);

// Texture slot t0 is always the albedo of a texture
texture2D texAlbedo : register(t0);

// Sampler Slot s0 is always the default engine sampler
SamplerState textureSampler : register(S0);

// The default vertex format
struct VertexData
{
    float3 position : POSITION;
    float3 normal : NORMAL;
    float2 uv : TEXCOORD;
};

// The default pixel format
struct PixelData
{
    float4 position : SV_Position;
    float2 texCoord : TEXCOORD;
};
