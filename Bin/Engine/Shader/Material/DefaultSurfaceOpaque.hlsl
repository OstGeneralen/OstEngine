#include "../Shared/Resources.hlsli"
#include "../Shared/Material.hlsli"

Texture2D t_albedo : register(t0);
Texture2D t_normal : register(t1);
Texture2D t_orm : register(t2);

void MaterialMain( inout SurfaceProperties surface, inout SurfaceMaterial material )
{
    material.albedo = SampleRGB(surface.uv, t_albedo, TrilinearWrap);
    material.normal = SampleNormal(surface.uv, surface.normal, surface.tangent, surface.bitangent, t_normal, TrilinearWrap );
    SampleORM( surface.uv, t_orm, TrilinearWrap, material.ao, material.roughness, material.metallic );
}
