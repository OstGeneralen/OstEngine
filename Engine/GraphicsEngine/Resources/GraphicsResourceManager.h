// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Objects/ObjectHandles.h"
#include "GraphicsEngine/Resources/IGraphicsResourceManager.h"
#include "GraphicsEngine/Resources/MaterialFactory.h"

// Actual Resource Includes
#include "GraphicsEngine/Objects/Model.h"
#include "GraphicsEngine/Objects/Texture.h"

#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GraphicsResourceManager : public IGraphicsResourceManager
    {
    public:
        void Initialize(const RenderHardwareInterface& rhi);

        TextureHandle Create(const TextureCPUData& data) override;
        ModelHandle Create(const ModelCPUData& data) override;

        const Texture& Get(TextureHandle hnd) const override;
        const Model& Get(ModelHandle hnd) const override;
        const Mesh& Get(MeshHandle hnd) const override;

    private:
        SlotMap<Texture> _textures;
        SlotMap<Model> _models;
        SlotMap<Mesh> _meshes;

        MaterialFactory _materialFactory;

        const RenderHardwareInterface* _pRHI;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------