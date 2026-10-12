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

        virtual HTexture Create(const TextureCPUData& cpuData) = 0;
        virtual HModel Create(const ModelCPUData& cpuData) = 0;

        virtual void Release(HTexture handle) = 0;
        virtual void Release(HModel handle) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------