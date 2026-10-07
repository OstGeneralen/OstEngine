// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Container/List.h"
#include "Math/Color.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    enum EModelVertexData
    {
        EModelVertexData_Normal = 1 << 0,
        EModelVertexData_Tangent = 1 << 1,
        EModelVertexData_UV = 1 << 2,
        EModelVertexData_Color = 1 << 3,
        EModelVertexData_BoneData = 1 << 4,

        EModelVertexData_StaticMesh = EModelVertexData_Normal | EModelVertexData_Tangent | EModelVertexData_UV | EModelVertexData_Color,
        EModelVertexData_SkinnedMesh = EModelVertexData_StaticMesh | EModelVertexData_BoneData,
    };

    // This is just a vertex that contains all the data a vertex CAN hold.
    // The graphics API will have to translate this into a useful format before actually
    // generating any resources from it.
    struct ModelVertex
    {
        Vector4f position;    // ALWAYS PRESENT
        Vector3f normal;      // ONLY IF EModelVertexData_Normal
        Vector3f tangent;     // ONLY IF EModelVertexData_Tangent
        Vector2f uv;          // ONLY IF EModelVertexData_UV
        Color color;          // ONLY IF EModelVertexData_Color
        Vector4u boneIndexes; // ONLY IF EModelVertexData_BoneData
        Vector4f boneWeights; // ONLY IF EModelVertexData_BoneData
    };

    struct ModelCPUData
    {
        struct Mesh
        {
            struct BufferValue
            {
                SizeType count;
                SizeType offset;
            };

            BufferValue vertices;
            BufferValue indices;
            SizeType materialIndex;
        };

        SizeType numMaterials;

        EModelVertexData vertexLayoutMask;
        List<ModelVertex> vertexList;
        List<Uint32> indexList;
        List<Mesh> submeshes;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------