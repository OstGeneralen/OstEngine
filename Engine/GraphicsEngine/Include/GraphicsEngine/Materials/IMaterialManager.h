// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/IMaterial.h"
#include "GraphicsEngine/Materials/IMaterialInstance.h"

// ------------------------------------------------------------

namespace ost
{
    class IMaterialManager
    {
    public:
        virtual ~IMaterialManager() = default;

        virtual HMaterial CreateMaterial(const MaterialDesc& desc) = 0;
        virtual HMaterialInstance CreateInstance(HMaterial fromMaterialHandle) = 0;

        virtual IMaterial& GetMaterial(HMaterial handle) = 0;
        virtual const IMaterial& GetMaterial(HMaterial handle) const = 0;

        virtual IMaterialInstance& GetMaterialInstance(HMaterialInstance handle) = 0;
        virtual const IMaterialInstance& GetMaterialInstance(HMaterialInstance handle) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------