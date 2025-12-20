cbuffer WorldInfo : register(b0)
{
    row_major float4x4 viewProjectionMat;
    
    float3 sunDirection;
    float sdpad;
    
    float totalTime;
    float3 ttpad;
}

cbuffer PerObject : register(b1)
{
    row_major float4x4 modelMat;
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
    float4 sunIntensityColor : COLOR;
};

Texture2D tex : register(t0);
SamplerState s : register(s0);

pixelInfo vsMain(vertexInfo input)
{
    pixelInfo output;
    
    float4x4 mvpMat = mul(modelMat, viewProjectionMat);
    float4 posV4 = float4(input.position.x, input.position.y, input.position.z, 1.0f);
    float4 normV4 = float4(input.normal.x, input.normal.y, input.normal.z, 0.0f);
    
    float4 normWorld = mul(normV4, modelMat);
    normWorld = normalize(normWorld);
    
    output.sunIntensityColor = float4(1, 1, 1, 1) * ((dot(normWorld.xyz, -sunDirection) + 1.0f) * 0.5f);
    output.position = mul(posV4, mvpMat);
    output.pixelUV = input.vertexUV;
    return output;
}

float4 psMain( pixelInfo input ) : SV_TARGET
{
    float4 color = tex.Sample(s, input.pixelUV);
    float3 colorRgb = color.rgb * input.sunIntensityColor.r;
    color.rgb = colorRgb;
    return color;
}