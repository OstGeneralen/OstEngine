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

    struct RenderCommand
    {
        const Mesh* pMesh;
        Matrix4x4 transform;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------