// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Objects/ObjectHandles.h"
#include "GraphicsEngine/Rendering/MaterialFactory.h"

#include <Container/SlotMap.h>

// Resource Types
#include "GraphicsEngine/Objects/Material.h"
#include "GraphicsEngine/Objects/Model.h"
#include "GraphicsEngine/Objects/Texture.h"

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GraphicsResourceManager
    {
    public:
        void Initialize(const RenderHardwareInterface& rhi);

        MaterialHandle Create(const MaterialDesc& desc);
        TextureHandle Create(const ResourceTextureDesc& desc);
        ModelHandle Create(const StaticModelDesc& desc);

        const Texture& Get(TextureHandle hnd) const;
        const Material& Get(MaterialHandle hnd) const;
        const Model& Get(ModelHandle hnd) const;
        const Mesh& Get(MeshHandle hnd) const;

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