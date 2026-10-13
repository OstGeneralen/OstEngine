#ifndef SHADER_COMMON_HLSLI
#define SHADER_COMMON_HLSLI

float3 ExtractAndUnpackNormal( float2 sampledNormal )
{
    float3 unpacked = float3( (sampledNormal * 2) - float2(1,1), 0 );

    float x2 = unpacked.x * unpacked.x;
    float y2 = unpacked.y * unpacked.y;
    unpacked.z = sqrt( 1.0f - saturate(  x2 + y2 ));
    return unpacked;
}

#endif