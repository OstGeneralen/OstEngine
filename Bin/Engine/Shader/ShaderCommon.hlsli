#ifndef SHADER_COMMON_HLSLI
#define SHADER_COMMON_HLSLI

struct VSTangentSpace 
{
    float3 tangent;
    float3 normal;
    float3 bitangent;
};

VSTangentSpace VSCalculateTangentSpace( float4x4 transform, float3 normal, float3 tangent )
{
    row_major float3x3 toWorld = (float3x3)transform;
    
    VSTangentSpace ts;
    ts.tangent = normalize( mul(tangent, toWorld) );
    ts.normal = normalize(mul(normal, toWorld));
    ts.bitangent = normalize( cross(ts.normal, ts.tangent) );

    return ts;
}

float3 ExtractAndUnpackNormal( float2 sampledNormal )
{
    float3 unpacked = float3( (sampledNormal * 2) - float2(1,1), 0 );

    float x2 = unpacked.x * unpacked.x;
    float y2 = unpacked.y * unpacked.y;
    unpacked.z = sqrt( 1.0f - saturate(  x2 + y2 ));
    return unpacked;
}

float3 CalculatePixelNormal( float2 sampledNormal, float3 surfaceNormal, float3 surfaceTangent, float3 surfaceBitangent )
{
    float3 T = normalize( surfaceTangent );
    float3 B = normalize(surfaceBitangent);
    float3 N = normalize(surfaceNormal);
    float3x3 TBN = float3x3(T,B,N);

    return mul( ExtractAndUnpackNormal(sampledNormal), TBN );
}

#endif