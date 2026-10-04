// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Objects/ObjectHandles.h"

// Resources
#include "GraphicsEngine/Objects/Material.h"
#include "GraphicsEngine/Objects/Model.h"
#include "GraphicsEngine/Objects/Texture.h"

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager
    {
    public:
        virtual ~IGraphicsResourceManager() = default;

        virtual MaterialHandle Create(const MaterialDesc& desc) = 0;
        virtual TextureHandle Create(const ResourceTextureDesc& desc) = 0;
        virtual ModelHandle Create(const StaticModelDesc& desc) = 0;

        virtual const Texture& Get(TextureHandle hnd) const = 0;
        virtual const Material& Get(MaterialHandle hnd) const = 0;
        virtual const Model& Get(ModelHandle hnd) const = 0;
        virtual const Mesh& Get(MeshHandle hnd) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------