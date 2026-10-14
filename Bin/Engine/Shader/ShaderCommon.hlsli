#ifndef SHADER_COMMON_HLSLI
#define SHADER_COMMON_HLSLI

struct VSTangentSpace {
    float3 tangent;
    float3 normal;
    float3 bitangent;
};

float3 ReconstructWorldPosition(float2 uv, float depth, float4x4 inverseViewProj) {
    float2 ndcUV = uv * float2(2.0f, -2.0f) + float2(-1.0f, 1.0f);
    float4 ndcPos = float4(ndcUV, depth, 1.0f);
    float4 worldPos = mul(ndcPos, inverseViewProj);
    return float3(worldPos.xyz) / worldPos.w;
}

VSTangentSpace VSCalculateTangentSpace(float4x4 transform, float3 normal, float3 tangent) {
    row_major float3x3 toWorld = (float3x3)transform;

    VSTangentSpace ts;
    ts.tangent = normalize(mul(tangent, toWorld));
    ts.normal = normalize(mul(normal, toWorld));
    ts.bitangent = normalize(cross(ts.normal, ts.tangent));

    return ts;
}

float3 PackNormal(float3 unpacked) {
    return (unpacked + float3(1,1,1)) * 0.5f;
}

float3 UnpackNormal(float3 packed) {
    return (packed * 2) - float3(1,1,1);
}

float3 ExtractAndUnpackNormal(float2 sampledNormal) {
    float3 unpacked = float3((sampledNormal * 2) - float2(1,1), 0);

    float x2 = unpacked.x * unpacked.x;
    float y2 = unpacked.y * unpacked.y;
    unpacked.z = sqrt(1.0f - saturate(x2 + y2));
    return unpacked;
}

float3 CalculatePixelNormal(float2 sampledNormal, float3 surfaceNormal, float3 surfaceTangent, float3 surfaceBitangent) {
    float3 T = normalize(surfaceTangent);
    float3 B = normalize(surfaceBitangent);
    float3 N = normalize(surfaceNormal);
    float3x3 TBN = float3x3(T,B,N);

    return mul(ExtractAndUnpackNormal(sampledNormal), TBN);
}

float3 GammaCorrectOutput(float3 rgb, float gamma) {
    const float f = 1.0f / gamma;
    return float3(pow(rgb.r, f), pow(rgb.g, f), pow(rgb.b, f));
}

#endif