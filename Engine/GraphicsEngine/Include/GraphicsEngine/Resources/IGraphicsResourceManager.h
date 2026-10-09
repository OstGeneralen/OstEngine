// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/ObjectHandles.h"

// Graphics Data Objects
#include "GraphicsEngine/Resources/ModelCPUData.h"
#include "GraphicsEngine/Resources/TextureCPUData.h"

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

        virtual void Release(TextureHandle handle) = 0;
        virtual void Release(ModelHandle handle) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------