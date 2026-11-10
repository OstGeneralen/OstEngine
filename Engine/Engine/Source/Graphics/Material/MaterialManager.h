// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Graphics/Material/MaterialClass.h"
#include "Engine/Graphics/Material/MaterialInstance.h"

#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class IGraphicsResourceManager;

    class MaterialManager
    {
    public:
        MaterialManager(IGraphicsResourceManager& gfxResourceManager);

        HMaterialClass CreateClass(const MaterialDesc& desc);

        MaterialClass& GetClass(HMaterialClass h);
        const MaterialClass& GetClass(HMaterialClass h) const;

    private:
        SlotMap<MaterialClass> _classes;

        IGraphicsResourceManager& _graphicsResources;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------