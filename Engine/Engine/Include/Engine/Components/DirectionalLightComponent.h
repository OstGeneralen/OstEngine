// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Components/LightComponent.h"

// ------------------------------------------------------------

namespace ost
{
    class DirectionalLightComponent : public LightComponent
    {
    private:
        void InitializeLightType( LightRenderProxy& proxy ) override;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------