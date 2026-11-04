// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/ObjectHandles.h"

// Graphics Data Objects
#include "GraphicsEngine/Resources/ModelCPUData.h"
#include "GraphicsEngine/Resources/ShaderCPUData.h"
#include "GraphicsEngine/Resources/TextureCPUData.h"

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct ITexture;
    struct IShader;

    class IGraphicsResourceManager
    {
    public:
        virtual ~IGraphicsResourceManager() = default;

        virtual HTexture Create(const TextureCPUData& cpuData) = 0;
        virtual List<HMesh> Create(const List<ModelVertex>& verts, const List<Uint32>& indices, const List<MeshCPUData>& meshes) = 0;
        virtual HShader Create(const ShaderCPUData& cpuData) = 0;

        virtual const ITexture& GetTexture(HTexture h) const = 0;
        virtual const IShader& GetShader(HShader h) const = 0;

        virtual void Release(HTexture handle) = 0;
        virtual void Release(HMesh handle) = 0;
        virtual void Release(HShader handle) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------