#include "../Shared/ShaderCommon.hlsli"
#include "../Shared/LayoutsMaster.hlsli"
#include "../Shared/Resources.hlsli"
#include "../Shared/Material.hlsli"

Texture2D tex_albedo : register(t0);
Texture2D tex_normal : register(t1);
Texture2D tex_orm : register(t2);

GBuffer PSMain(StaticSurfaceFragment frag) {
    Material material;
    material.albedo = tex_albedo.Sample(TrilinearWrap, frag.UV).rgb;
    material.worldPosition = frag.WorldPosition;

    float2 normal = tex_normal.Sample(TrilinearWrap, frag.UV).rg;
    material.normal = CalculatePixelNormal(normal, frag.Normal, frag.Tangent, frag.Bitangent);

    float3 orm = tex_orm.Sample(TrilinearWrap, frag.UV).rgb;
    material.ao = orm.r;
    material.roughness = orm.g;
    material.metallic = orm.b;

    MaterialMain(material);

    GBuffer gbuf;
    gbuf.albedo = float4(material.albedo, 1);
    gbuf.normal = float4(PackNormal(material.normal), 1);
    gbuf.orm = float4(material.ao, material.roughness, material.metallic, 1);
    return gbuf;
}