// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/IGraphicsResourceManager.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

// Actual Resource Includes
#include "GraphicsEngine/Materials/Material.h"
#include "GraphicsEngine/Materials/MaterialInstance.h"
#include "Objects/Buffer.h"
#include "Objects/Model.h"
#include "Objects/PipelineStateObject.h"
#include "Objects/Texture.h"

#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GraphicsResourceManager : public IGraphicsResourceManager
    {
    public:
        void Initialize(const RenderHardwareInterface& rhi);

        const Texture& Get(TextureHandle hnd) const;
        const Model& Get(ModelHandle hnd) const;
        const Mesh& Get(MeshHandle hnd) const;
        const Buffer& Get(BufferHandle hnd) const;
        const Material& Get(MaterialHandle hnd) const;

        const BufferHandle CreateBuffer(SizeType numBytes);

        const RenderHardwareInterface& GetRHI() const;

    public: // IGraphicsResourceManager
        TextureHandle Create(const TextureCPUData& data) override;
        ModelHandle Create(const ModelCPUData& data) override;

        virtual void Release(TextureHandle handle) override;
        virtual void Release(ModelHandle handle) override;

    private:
        SlotMap<Texture> _textures;
        SlotMap<Model> _models;
        SlotMap<Mesh> _meshes;
        SlotMap<Buffer> _buffers;

        const RenderHardwareInterface* _pRHI;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------