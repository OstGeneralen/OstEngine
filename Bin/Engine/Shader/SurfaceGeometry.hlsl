#include "Shared/LayoutsMaster.hlsli"
#include "Shared/MaterialImpl.hlsli"
#include "Shared/Material.hlsli"
#include "Shared/ShaderCommon.hlsli"
#include "Shared/Resources.hlsli"

Texture2D tex_albedo : register(t0);
Texture2D tex_normal : register(t1);
Texture2D tex_orm : register(t2);

GBuffer PSMain(StaticSurfaceFragment frag) {
    SurfaceProperties surface;
    surface.normal = frag.Normal;
    surface.tangent = frag.Tangent;
    surface.bitangent = frag.Bitangent;
    surface.uv = frag.UV;
    surface.worldPos = frag.WorldPosition;

    SurfaceMaterial material;
    material.albedo = float3(0,0,0);
    material.normal = float3(0.5f, 0.5f, 1);
    material.ao = 0;
    material.roughness = 1;
    material.metallic = 0;

    MaterialMain(surface, material);

    GBuffer gbuf;
    gbuf.albedo = float4(material.albedo, 1);
    gbuf.normal = float4(PackNormal(material.normal), 1);
    gbuf.orm = float4(material.ao, material.roughness, material.metallic, 1);
    return gbuf;
}