cbuffer WorldInfo : register(b0)
{
    float4x4 viewProjectionMat;
    float totalTime;
    float3 padding;
}

cbuffer PerObject : register(b1)
{
    float4x4 modelMat;
}

struct vertexInfo
{
    float3 position : POSITION;
    float3 normal: NORMAL;
    float2 vertexUV : TEXCOORD0;
};

struct pixelInfo
{
    float4 position : SV_Position;
    float2 pixelUV : TEXCOORD0;
};

Texture2D tex : register(t0);
SamplerState s : register(s0);

pixelInfo vsMain(vertexInfo input)
{
    pixelInfo output;
    
    float4x4 mvpMat = modelMat * viewProjectionMat;
    float4 posV4 = float4(input.position.x, input.position.y, input.position.z, 1.0f);
    
    output.position = mul(mvpMat, posV4);
    output.pixelUV = input.vertexUV;
    return output;
}

float4 psMain( pixelInfo input ) : SV_TARGET
{
    return tex.Sample(s, input.pixelUV);
}