#include "../ShaderCore.hlsli"
#include "../ShaderCommon.hlsli"

Texture2D tex_albedo : register(t0);
Texture2D tex_normal : register(t0);
Texture2D tex_orm : register(t0);

struct SurfaceData
{
    float3 albedo;
    float3 normal;
    float ao;
    float roughness;
    float metallic;
};

#ifdef MATERIAL_SHADER
#include "MATERIAL"
#else
void MaterialMain( inout SurfaceData d )
{
}
#endif

GBuffer PSMain( SurfacePixel frag )
{
    SurfaceData surface;
    surface.albedo = tex_albedo.Sample(TrilinearWrap, frag.UV).rgb;

    float2 normal = tex_normal.Sample(TrilinearWrap, frag.UV).rg;
    surface.normal = CalculatePixelNormal(normal, frag.Normal, frag.Tangent, frag.Bitangent);

    float3 orm = tex_orm.Sample(TrilinearWrap, frag.UV).rgb;
    surface.ao = orm.r;
    surface.roughness = orm.g;
    surface.metallic = orm.b;

    MaterialMain( surface );

    GBuffer gbuf;
    gbuf.Albedo = float4(surface.albedo, 1);
    gbuf.Normal = float4(PackNormal(surface.normal), 1);
    gbuf.ORM = float4(surface.ao, surface.roughness, surface.metallic, 1);
    return gbuf;
}