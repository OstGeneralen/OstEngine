#ifndef MATERIAL_IMPL_HLSLI
#define MATERIAL_IMPL_HLSLI
#include "Material.hlsli"

#ifdef SHADER_VARIANT_MATERIAL
#include "MATERIAL" // This will be swapped for the actual material shader file :)
#else
void MaterialMain(inout SurfaceProperties properties, inout SurfaceMaterial material) {
    // No-op (not a material shader)
}
#endif // SHADER_VARIANT_MATERIAL

#endif // MATERIAL_IMPL_HLSLI