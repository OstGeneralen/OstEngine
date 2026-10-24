// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/SpotLightComponent.h"

#include "Engine/World/Actor.h"

#include <Math/Units.h>

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
    proxy.proxyData.radius = 0.1f;
    proxy.proxyData.outerRadius = 0.2f;
    proxy.proxyData.range = 1.0f;
}

// ------------------------------------------------------------

List<ComponentProperty> ost::SpotLightComponent::GeneratePropertySet()
{
    // Validate all values
    List<ComponentProperty> props = {};

    props.Add(ComponentProperty("Color", TypeID::Get<Color>(), &GetProxy().proxyData.color));
    props.Add(ComponentProperty("Intensity", TypeID::Get<Float32>(), &GetProxy().proxyData.intensity));
    props.Add(ComponentProperty("Range", TypeID::Get<Float32>(), &GetProxy().proxyData.range));
    props.Add(ComponentProperty("Inner Angle", TypeID::Get<Radians>(), &GetProxy().proxyData.radius));
    props.Add(ComponentProperty("Outer Angle", TypeID::Get<Radians>(), &GetProxy().proxyData.outerRadius));

    return props;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------