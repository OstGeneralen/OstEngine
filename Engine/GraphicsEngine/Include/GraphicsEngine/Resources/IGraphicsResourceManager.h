// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

// Graphics Data Objects
#include "GraphicsEngine/Resources/Descriptors/MeshDesc.h"
#include "GraphicsEngine/Resources/Descriptors/ShaderDesc.h"
#include "GraphicsEngine/Resources/Descriptors/TextureDesc.h"

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

        virtual HTexture Create(const TextureDesc& desc) = 0;
        virtual HMesh Create(const RawVertexData& vertexData, const List<Uint32>& indices) = 0;
        virtual List<HMesh> Create(const RawVertexData& vertexData, const List<Uint32>& indices, const List<MeshDesc>& meshDescs) = 0;
        virtual HShader Create(const ShaderDesc& desc) = 0;

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