// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/IGraphicsResourceManager.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

// Materials
#include "GraphicsEngine/Materials/IMaterialManager.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstance.h"

// Actual Resource Includes
#include "Objects/Buffer.h"
#include "Objects/Model.h"
#include "Objects/PipelineStateObject.h"
#include "Objects/Texture.h"

#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GraphicsResourceManager : public IGraphicsResourceManager, public IMaterialManager
    {
    public:
        void Initialize(const RenderHardwareInterface& rhi);

        const Texture& Get(HTexture hnd) const;
        const Model& Get(HModel hnd) const;
        const Mesh& Get(HMesh hnd) const;
        const Material& Get( HMaterial hnd ) const;        
        const MaterialInstance& Get( HMaterialInstance hnd ) const;        

        const HBuffer CreateBuffer(SizeType numBytes);

        const RenderHardwareInterface& GetRHI() const;

        // BEGIN IGraphicsResourceManager
        HTexture Create(const TextureCPUData& data) override;
        HModel Create(const ModelCPUData& data) override;

        const ITexture& GetTexture( HTexture h ) const override;

        virtual void Release(HTexture handle) override;
        virtual void Release(HModel handle) override;
        // END IGraphicsResourceManager

        // TODO: Maybe reconsider if this is where this interface should be implemented
        // Was useful for now since it already sits on a non-owning reference to the RHI
        // BEGIN IMaterialManager
        HMaterial CreateMaterial(const MaterialDesc& desc) override;
        HMaterialInstance CreateInstance(HMaterial fromMaterialHandle) override;

        IMaterial& GetMaterial(HMaterial handle) override;
        const IMaterial& GetMaterial(HMaterial handle) const override;

        IMaterialInstance& GetMaterialInstance(HMaterialInstance handle) override;
        const IMaterialInstance& GetMaterialInstance(HMaterialInstance handle) const override;
        // END IMaterialManager

    private:
        SlotMap<Texture> _textures;
        SlotMap<Model> _models;
        SlotMap<Mesh> _meshes;
        SlotMap<Buffer> _buffers;

        SlotMap<Material> _materials;
        SlotMap<MaterialInstance> _materialInstances;

        const RenderHardwareInterface* _pRHI;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------