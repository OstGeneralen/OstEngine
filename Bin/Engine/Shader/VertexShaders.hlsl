#include "ShaderCore.hlsli"
#include "ShaderCommon.hlsli"

// ------------------------------------------------------------

FullscreenPixel VSMain_Fullscreen(FullscreenVertex vertex) {
    FullscreenPixel px;
    px.Position = vertex.Position;
    px.UV = vertex.UV;
    return px;
}

// ------------------------------------------------------------

SurfacePixel VSMain_Surface(SurfaceVertex vertex) {
    float4 worldPosition = mul(vertex.Position, ObjectBuf_Transform);

    SurfacePixel output;
    output.BaseColor = vertex.BaseColor;

    // Calculate TBN
    VSTangentSpace ts = VSCalculateTangentSpace(ObjectBuf_Transform, vertex.Normal, vertex.Tangent);
    output.Tangent = ts.tangent;
    output.Normal = ts.normal;
    output.Bitangent = ts.bitangent;

    output.Position = mul(worldPosition, FrameBuf_ViewProjection);
    output.WorldPosition = worldPosition.xyz;
    output.ViewPosition = mul(vertex.Position, FrameBuf_ViewInverse);
    output.UV = vertex.UV;

    return output;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------