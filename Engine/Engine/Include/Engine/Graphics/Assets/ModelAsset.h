// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Asset/Asset.h"

#include <Container/List.h>
#include <GraphicsEngine/Resources/ObjectHandles.h>

// ------------------------------------------------------------

namespace ost
{
    struct Submesh
    {
        SizeType vertexCount;
        SizeType vertexOffset;
        SizeType indexCount;
        SizeType indexOffset;
        SizeType materialIndex;
    };

    class ModelAsset : public Asset
    {
    public:
        ModelAsset()
            : Asset{}
        {
        }
        ModelAsset(HVertexBuffer hVB, HIndexBuffer hIB, List<Submesh>&& subMsh)
            : _vertexBufferHandle{hVB}
            , _indexBufferHandle{hIB}
            , _submeshes{std::move(subMsh)}
        {
        }
        ModelAsset(const ModelAsset&) = delete;
        ModelAsset(ModelAsset&& asset) noexcept = default;
        ~ModelAsset();

        ModelAsset& operator=(const ModelAsset&) = delete;
        ModelAsset& operator=(ModelAsset&&) noexcept = default;

        HVertexBuffer GetVertexBuffer() const
        {
            return _vertexBufferHandle;
        }
        HIndexBuffer GetIndexBuffer() const
        {
            return _indexBufferHandle;
        }
        const List<Submesh>& GetSubmeshes() const
        {
            return _submeshes;
        }

        TypeID AssetTypeID() const override
        {
            return TypeID::Get<ModelAsset>();
        }

    private:
        HVertexBuffer _vertexBufferHandle;
        HIndexBuffer _indexBufferHandle;
        List<Submesh> _submeshes;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------