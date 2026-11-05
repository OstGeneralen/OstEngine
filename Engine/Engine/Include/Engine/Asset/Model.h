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

    class Model : public Asset
    {
    public:
        Model()
            : Asset{}
        {
        }
        Model(HVertexBuffer hVB, HIndexBuffer hIB, List<Submesh>&& subMsh)
            : _vertexBufferHandle{hVB}
            , _indexBufferHandle{hIB}
            , _submeshes{std::move(subMsh)}
        {
        }
        Model(const Model&) = delete;
        Model(Model&& asset) noexcept
            : Asset{std::move(asset)}
            , _vertexBufferHandle{std::move(asset._vertexBufferHandle)}
            , _indexBufferHandle{std::move(asset._indexBufferHandle)}
            , _submeshes{std::move(asset._submeshes)}
        {
        }
        ~Model();

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
            return TypeID::Get<Model>();
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