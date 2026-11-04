// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/IGraphicsResourceManager.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

// Actual Resource Includes
#include "Objects/Buffer.h"
#include "Objects/Mesh.h"
#include "Objects/PipelineStateObject.h"
#include "Objects/Shader.h"
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

        const Texture& Get(HTexture hnd) const;
        const Mesh& Get(HMesh hnd) const;
        const Shader& Get(HShader hnd) const;

        const HBuffer CreateBuffer(SizeType numBytes);

        const RenderHardwareInterface& GetRHI() const;

        // BEGIN IGraphicsResourceManager
        HTexture Create(const TextureDesc& desc) override;
        HMesh Create(const RawVertexData& vertexData, const List<Uint32>& indices) override;
        List<HMesh> Create(const RawVertexData& vertexData, const List<Uint32>& indices, const List<MeshDesc>& meshDescs) override;
        HShader Create(const ShaderDesc& desc) override;

        const ITexture& GetTexture(HTexture h) const override;
        const IShader& GetShader(HShader h) const override;

        virtual void Release(HTexture handle) override;
        virtual void Release(HMesh handle) override;
        void Release(HShader handle) override;
        // END IGraphicsResourceManager

    private:
        SlotMap<Texture> _textures;
        SlotMap<Mesh> _meshes;
        SlotMap<Buffer> _buffers;
        SlotMap<Shader> _shaders;

        const RenderHardwareInterface* _pRHI;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------