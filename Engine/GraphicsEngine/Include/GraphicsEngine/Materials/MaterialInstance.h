// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/MaterialPropertyCollection.h"

#include <OstTypes.h>
#include <string>

// ------------------------------------------------------------

namespace ost
{
    class Material;

    class MaterialInstance
    {
    public:
        virtual ~MaterialInstance() = default;

        MaterialPropertyCollection& Properties();
        const MaterialPropertyCollection& Properties() const;

    protected:
        Material* _pRootMaterial;
        MaterialPropertyCollection _propertyCollection;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------