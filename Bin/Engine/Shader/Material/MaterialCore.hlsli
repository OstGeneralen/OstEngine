struct MaterialVertexData
{
    float4 vertexWorldPos;
    float4 vertexColor;
    float2 vertexUV;
};

struct MaterialPixelData
{
    float4 color;
    float3 albedo;
    float3 normal;
    float2 uv;
};

void Material_VS( inout MaterialVertexData data );
void Material_PS( inout MaterialPixelData data );