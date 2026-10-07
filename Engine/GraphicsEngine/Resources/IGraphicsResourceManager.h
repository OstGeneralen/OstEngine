// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Objects/ObjectHandles.h"

// Graphics Data Objects
#include <Data/TextureCPUData.h>
#include <Data/ModelCPUData.h>


// ------------------------------------------------------------

namespace ost
{
    struct Texture;
    struct Model;
    struct Mesh;

    class IGraphicsResourceManager
    {
    public:
        virtual ~IGraphicsResourceManager() = default;

        virtual TextureHandle Create(const TextureCPUData& cpuData) = 0;
        virtual ModelHandle Create(const ModelCPUData& cpuData) = 0;

        virtual const Texture& Get(TextureHandle hnd) const = 0;
        virtual const Model& Get(ModelHandle hnd) const = 0;
        virtual const Mesh& Get(MeshHandle hnd) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------