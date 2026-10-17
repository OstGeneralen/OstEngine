// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Components/LightComponent.h"

// ------------------------------------------------------------

namespace ost
{
    class SpotLightComponent : public LightComponent
    {
    public:
        void SetInnerRadius( Float32 r );
        void SetOuterRadius( Float32 r );
        void SetRange( Float32 r );

    private:
        void InitializeLightType( LightRenderProxy& proxy ) override;

    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------