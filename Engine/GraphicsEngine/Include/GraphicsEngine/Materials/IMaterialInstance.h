// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/IMaterialPropertyCollection.h"
#include "GraphicsEngine/Materials/MaterialTextureCollection.h"

#include <Utility/TypedIntegerHandle.h>

// ------------------------------------------------------------

namespace ost
{
    using HMaterialInstance = TypedIntegerHandle<struct HND_MaterialInstance>;

    class IMaterialInstance
    {
    public:
        virtual ~IMaterialInstance() = default;

        virtual IMaterialPropertyCollection& Properties() = 0;
        virtual const IMaterialPropertyCollection& Properties() const = 0;
        virtual MaterialTextureCollection& Textures() = 0;
        virtual const MaterialTextureCollection& Textures() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------