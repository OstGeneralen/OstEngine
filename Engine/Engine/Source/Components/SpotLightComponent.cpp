// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/SpotLightComponent.h"

#include "Engine/World/Actor.h"

using namespace ost;

// ------------------------------------------------------------

void SpotLightComponent::SetInnerRadius(Float32 r)
{
    GetProxy().proxyData.radius = r;
}

void SpotLightComponent::SetOuterRadius(Float32 r)
{
    GetProxy().proxyData.outerRadius = r;
}

void SpotLightComponent::SetRange(Float32 r)
{
    GetProxy().proxyData.range = r;
}

void SpotLightComponent::InitializeLightType(LightRenderProxy& proxy)
{
    proxy.proxyData.type = ELightType::Spot;
    proxy.proxyData.radius = 0.01f;
    proxy.proxyData.outerRadius = 0.5f;
    proxy.proxyData.range = 1.0f;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------