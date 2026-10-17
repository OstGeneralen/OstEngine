// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/SpotLightComponent.h"

#include "Engine/World/Actor.h"

using namespace ost;

// ------------------------------------------------------------

void SpotLightComponent::SetInnerRadius(Float32 r)
{
    GetProxy().radius = r;
}

void SpotLightComponent::SetOuterRadius(Float32 r)
{
    GetProxy().outerRadius = r;
}

void SpotLightComponent::SetRange(Float32 r)
{
    GetProxy().range = r;
}

void SpotLightComponent::InitializeLightType(LightRenderProxy& proxy)
{
    proxy.type = ELightProxyType::Spot;
    proxy.radius = 0.01f;
    proxy.outerRadius = 0.5f;
    proxy.range = 1.0f;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------