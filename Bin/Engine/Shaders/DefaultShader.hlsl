struct vertexInfo
{
    float4 position : POSITION;
    float4 color : COLOR;
};

struct pixelInfo
{
    float4 position : SV_Position;
    float4 color : COLOR;
};

float4 Color : register(b0);

pixelInfo vertexMain(vertexInfo input)
{
    pixelInfo output;
    output.position = input.position;
    output.color = Color;
    return output;
}

float4 pixelMain( pixelInfo input ) : SV_TARGET
{
    return input.color;
}