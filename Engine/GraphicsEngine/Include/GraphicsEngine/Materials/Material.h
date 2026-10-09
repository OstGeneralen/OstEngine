// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/MaterialPropertyCollection.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <string>

// ------------------------------------------------------------

namespace ost
{
    class Material
    {
    public:
        Material(const MaterialPropertiesDesc& propertiesDesc);
        Material(const Material&) = delete;
        Material(Material&&) noexcept;

        void PopulateInstanceDefaults(MaterialPropertyCollection& instancePropCollection) const;
        PSOHandle GetPSOHandle() const;

    private:
        PSOHandle _hPSO;
        MaterialPropertyCollection _propertyDefaults;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------