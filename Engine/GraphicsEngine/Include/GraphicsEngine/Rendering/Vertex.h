// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Container/List.h>
#include <Math/Color.h>
#include <Math/Vector2.h>
#include <Math/Vector3.h>
#include <Math/Vector4.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EVertexType
    {
        StaticMesh,
        BlitMesh,
    };

    struct StaticMeshVertex
    {
        Vector4f position;
        Vector3f normal;
        Vector3f tangent;
        Color color;
        Vector2f uv;
    };

    struct BlitMeshVertex
    {
        Vector4f position;
        Vector2f uv;
    };

    struct RawVertexData
    {
        inline SizeType GetVertexByteSize() const
        {
            switch (type)
            {
            case EVertexType::StaticMesh:
                return sizeof(StaticMeshVertex);
            case EVertexType::BlitMesh:
                return sizeof(BlitMeshVertex);
            }
            return 0;
        }

        inline SizeType GetVertexCount() const
        {   
            return bytes.GetSize() / GetVertexByteSize();
        }

        inline const void* GetVertexData() const
        {
            return bytes.GetData();
        }

        EVertexType type;
        List<Uint8> bytes;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------