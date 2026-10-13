struct MaterialVertexData
{
    float4 vertexWorldPos;
    float4 vertexColor;
    float2 vertexUV;
};

struct MaterialPixelData
{
    float4 color;
};

void Material_VS( inout MaterialVertexData data );
void Material_PS( inout MaterialPixelData data );