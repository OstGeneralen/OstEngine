#include "../ShaderCore.hlsli"
#include "MaterialCore.hlsli"

Texture2D Tex_albedo : register(t0);
Texture2D Tex_normal : register(t1);
Texture2D Tex_orm : register(t2);

void MaterialSurface(MaterialPixelInput p, inout MaterialSurfaceData surface) {
    surface.albedo = Tex_albedo.Sample(TrilinearWrap, p.uv).rgb;
    surface.normal = Material_ApplyNormalMap(Tex_normal.Sample(TrilinearWrap, p.uv).rg, p);

    float3 ORM = Tex_orm.Sample(TrilinearWrap, p.uv).rgb;
    surface.ao = ORM.r;
    surface.roughness = ORM.g;
    surface.metallicness = ORM.b;
}