// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <OstTypes.h>

#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    struct Mesh;
    class Material;
    class MaterialInstance;
    struct Texture;
    struct Model;
    class RenderCommandContext;
    struct Buffer;

    struct RenderCommand
    {
        const Mesh* pMesh;
        const Model* pModel;
        const Material* pMaterial;
        const MaterialInstance* pMaterialInstance;
        Matrix4x4 transform;

        void Execute(RenderCommandContext& ctx, const Buffer& objectBuffer) const;
        void ExecuteDeferred(RenderCommandContext& ctx, const Buffer& objectBuffer) const;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------