struct vertexInfo
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct pixelInfo
{
    float4 position : SV_POSITION;
    float4 color : COLOR;
};

SamplerState Texture;
float4x4 WorldView;

pixelInfo vertexMain(vertexInfo input)
{
    pixelInfo output;
    output.position = mul(WorldView, float4(input.position.xyz, 1));
    output.color = input.color;
    return output;
}

float4 pixelMain( pixelInfo input ) : SV_TARGET
{
    return input.color;
}