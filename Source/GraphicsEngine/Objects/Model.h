// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Objects/Buffer.h"
#include "GraphicsEngine/Objects/ObjectHandles.h"
#include "GraphicsEngine/RHI/RHIMinimal.h"
#include "GraphicsEngine/Rendering/Vertex.h"

#include <OstTypes.h>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct StaticModelDesc
    {
        struct Submesh
        {
            SizeType vertexOffset;
            SizeType vertexCount;
            SizeType indexOffset;
            SizeType indexCount;
            SizeType materialIndex;
        };

        List<SurfaceVertex> vertices;
        List<Uint32> indices;
        List<Submesh> meshes;
    };

    struct Model
    {
        List<MeshHandle> meshHandles;
        List<MaterialHandle> materials;

        Buffer vertexBuffer;
        Buffer indexBuffer;
    };

    struct Mesh
    {
        SizeType vertexOffset;
        SizeType indexOffset;
        SizeType indexCount;
        SizeType vertexCount;
        SizeType materialIndex;

        Buffer vertexBuffer;
        Buffer indexBuffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------