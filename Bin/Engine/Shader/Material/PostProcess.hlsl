#include "../Shared/ShaderCommon.hlsli"
#include "../Shared/LayoutsMaster.hlsli"
#include "../Shared/Resources.hlsli"
#include "../Shared/Material.hlsli"

Texture2D tex_sceneColor : register(t0);
Texture2D tex_sceneNormal : register(t1);
Texture2D tex_sceneOrm : register(t2);
Texture2D tex_sceneDepth : register(t3);

float4 PSMain(BlitFragment frag) : SV_Target {
    Material material;
    material.albedo = tex_sceneColor.Sample(PointClamp, frag.UV).rgb;
    material.normal = UnpackNormal(tex_sceneNormal.Sample(PointClamp, frag.UV).rgb);
    material.uv = frag.UV;
    material.worldPosition = ReconstructWorldPosition(frag.UV,  tex_sceneDepth.Sample(PointClamp, frag.UV).r, FrameBuf_ViewInverse);

    float3 orm = tex_sceneOrm.Sample(PointClamp, frag.UV).rgb;
    material.ao = orm.r;
    material.roughness = orm.g;
    material.metallic = orm.b;

    MaterialMain(material);

    return float4(GammaCorrectOutput(material.albedo.rgb, 1.95), 1);
}