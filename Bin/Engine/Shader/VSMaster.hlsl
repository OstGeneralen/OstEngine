#include "Shared/ShaderCommon.hlsli"
#include "LayoutsMaster.hlsli"
#include "ShaderCore.hlsli"

// ------------------------------------------------------------

#ifdef SHADER_VARIANT_SURFACE_STATIC
StaticSurfaceFragment VSMain(StaticSurfaceVertex vertex) {
    float4 worldPosition = mul(vertex.Position, ObjectBuf_Transform);

    StaticSurfaceFragment output;
    output.BaseColor = vertex.BaseColor;
    VSTangentSpace ts = VSCalculateTangentSpace(ObjectBuf_Transform, vertex.Normal, vertex.Tangent);
    output.Tangent = ts.tangent;
    output.Bitangent = ts.bitangent;
    output.Normal = ts.normal;

    output.Position = mul(worldPosition, FrameBuf_ViewProjection);
    output.WorldPosition = worldPosition;
    output.ViewPosition = mul(vertex.Position, FrameBuf_ViewInverse);
    output.UV = vertex.UV;

    return output;
}
#endif

// ------------------------------------------------------------

#ifdef SHADER_VARIANT_BLIT
BlitPixel VSMain(BlitVertex vertex) {
    BlitPixel output;
    output.Position = vertex.Position;
    output.UV = vertex.UV;
    return output;
}
#endif

// ------------------------------------------------------------