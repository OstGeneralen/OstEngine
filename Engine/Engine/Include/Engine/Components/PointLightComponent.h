// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Components/LightComponent.h"

// ------------------------------------------------------------

namespace ost
{
    class PointLightComponent : public LightComponent
    {
    public:
        void SetRadius(Float32 radius);
        Float32 GetRadius() const;

        List<ComponentProperty> GeneratePropertySet() override;

    private:
        void InitializeLightType(LightRenderProxy& proxy) override;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------