// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/IMaterialPropertyCollection.h"
#include "GraphicsEngine/Materials/MaterialTextureCollection.h"

#include <Utility/TypedIntegerHandle.h>

// ------------------------------------------------------------

namespace ost
{
    using HMaterial = TypedIntegerHandle<struct HND_Material>;

    struct MaterialDesc
    {
        EMaterialDomain domain;
        std::string materialShaderPath;
    };

    class IMaterial
    {
    public:
        virtual ~IMaterial() = default;

        virtual IMaterialPropertyCollection& GetPropertyDefaults() = 0;
        virtual MaterialTextureCollection& GetTextureDefaults() = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------