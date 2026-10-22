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

List<ComponentProperty> ost::PointLightComponent::GeneratePropertySet()
{
    List<ComponentProperty> properties = {};
    properties.Add(ComponentProperty("Color", TypeID::Get<Color>(), &GetProxy().proxyData.color));
    properties.Add(ComponentProperty("Intensity", TypeID::Get<Float32>(), &GetProxy().proxyData.intensity));
    properties.Add(ComponentProperty("Radius", TypeID::Get<Float32>(), &GetProxy().proxyData.radius));
    return properties;
}

void PointLightComponent::InitializeLightType(LightRenderProxy& proxy)
{
    proxy.proxyData.type = ELightType::Point;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------