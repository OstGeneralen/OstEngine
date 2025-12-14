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

pixelInfo vertexMain(vertexInfo input)
{
    pixelInfo output;
    output.position = input.position;
    output.color = input.color;
    return output;
}

float4 pixelMain( pixelInfo input ) : SV_TARGET
{
    return input.color;
}