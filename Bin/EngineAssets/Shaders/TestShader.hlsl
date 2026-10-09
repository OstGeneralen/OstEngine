#include "ShaderCore.hlsli"

SurfacePixel VSMain(SurfaceVertex vert)
{
    float4x4 toView = mul( ObjectBuf_Transform, FrameBuf_ViewMatrix );
    SurfacePixel pixel;
    pixel.Position = mul(vert.Position, toView);
    pixel.Normal = normalize(mul( float4(vert.Normal.xyz, 0), ObjectBuf_Transform ));
    pixel.Tangent = vert.Tangent;
    pixel.UV = vert.UV;
    pixel.BaseColor = vert.BaseColor;
    return pixel;
}

float4 PSMain(SurfacePixel pixel) : SV_Target
{
    // Calculate directional light
    float dirSunToNormalDot = dot((Light_SunDir.xyz * -1.0f), pixel.Normal);
    dirSunToNormalDot = (dirSunToNormalDot + 1) * 0.5f;
    float4 ambientColor = Light_AmbientCol;

    float3 pixelNormal = (pixel.Normal + 1.0f) * 0.5f;

    float4 finalColor = float4((pixel.BaseColor.rgb * dirSunToNormalDot) + ambientColor.rgb, 1);
    return saturate(finalColor);
}