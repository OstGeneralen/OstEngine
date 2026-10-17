// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/PointLightComponent.h"

using namespace ost;

// ------------------------------------------------------------

void PointLightComponent::SetRadius(Float32 r)
{
    GetProxy().proxyData.radius = r;
}

Float32 PointLightComponent::GetRadius() const
{
    return GetProxy().proxyData.radius;
}

void PointLightComponent::InitializeLightType(LightRenderProxy& proxy)
{
    proxy.proxyData.type = ELightType::Point;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------