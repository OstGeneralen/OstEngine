// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/PointLightComponent.h"

using namespace ost;

// ------------------------------------------------------------

void PointLightComponent::SetRadius(Float32 r)
{
    GetProxy().radius = r;
}

Float32 PointLightComponent::GetRadius() const
{
    return GetProxy().radius;
}

void PointLightComponent::InitializeLightType(LightRenderProxy& proxy)
{
    proxy.type = ELightProxyType::Point;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------