#include "ShaderCore.hlsli"

SurfacePixel VSMain(SurfaceVertex vert)
{
    float4x4 toView = mul( ObjectBuf_Transform, FrameBuf_ViewMatrix );
    SurfacePixel pixel;
    pixel.Position = mul(vert.Position, toView);
    pixel.Normal = mul( float4(vert.Normal.xyz, 0), ObjectBuf_Transform );
    pixel.Tangent = vert.Tangent;
    pixel.UV = vert.UV;
    pixel.BaseColor = float4(1,1,1,1);
    return pixel;
}

float4 PSMain(SurfacePixel pixel) : SV_Target
{
    return float4(pixel.BaseColor.rgb, 1);
}