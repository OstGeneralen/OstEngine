struct ViewProjection
{
    float4x4 viewMatrix;
    float4x4 projectMatrix;
    float totalTime;
};

struct VertexData
{
    float4x4 modelMatrix;
    float4 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD;
};

struct PixelData
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

SamplerState samplerState : register(s0);

Texture2D texAlbedo : register(t0);

ViewProjection viewProjection : register(b0);

PixelData vsMain( VertexData input )
{
    float4x4 mvp = input.modelMatrix * viewProjection.viewMatrix * viewProjection.projectMatrix;
    
    PixelData output;
    output.color = texAlbedo.Sample(samplerState, input.uv) * input.color;
    output.position = mul(mvp, input.position);
    return output;
}

float4 psMain(PixelData input) : SV_Target
{
    return input.color;
}
