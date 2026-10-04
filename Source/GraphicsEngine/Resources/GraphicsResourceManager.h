// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Objects/ObjectHandles.h"
#include "GraphicsEngine/Resources/IGraphicsResourceManager.h"
#include "GraphicsEngine/Resources/MaterialFactory.h"

#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GraphicsResourceManager : public IGraphicsResourceManager
    {
    public:
        void Initialize(const RenderHardwareInterface& rhi);

        MaterialHandle Create(const MaterialDesc& desc) override;
        TextureHandle Create(const ResourceTextureDesc& desc) override;
        ModelHandle Create(const StaticModelDesc& desc) override;

        const Texture& Get(TextureHandle hnd) const override;
        const Material& Get(MaterialHandle hnd) const override;
        const Model& Get(ModelHandle hnd) const override;
        const Mesh& Get(MeshHandle hnd) const override;

    private:
        SlotMap<Texture> _textures;
        SlotMap<Material> _materials;
        SlotMap<Model> _models;
        SlotMap<Mesh> _meshes;

        MaterialFactory _materialFactory;

        const RenderHardwareInterface* _pRHI;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------