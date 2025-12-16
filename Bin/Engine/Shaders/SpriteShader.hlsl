struct vertexInfo
{
    float4 position : POSITION;
    float4 color : COLOR;
    float2 uv : TEXCOORD0;
};

struct pixelInfo
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

float4 Color : register(b0);
Texture2D texture : register(t1);

SamplerState s : register(s0);

pixelInfo vertexMain(vertexInfo input)
{
    pixelInfo output;
    output.position = input.position;
    output.color = texture.Sample(s, input.uv);
    return output;
}

float4 pixelMain( pixelInfo input ) : SV_TARGET
{
    return input.color;
}