// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/DirectionalLightComponent.h"

#include "Engine/World/Actor.h"
#include "Engine/World/IComponentInitializer.h"
#include "World/SceneGraph.h"
#include "Engine/World/Transform.h"

using namespace ost;

// ------------------------------------------------------------

void ost::DirectionalLightComponent::InitializeLightType(LightRenderProxy& proxy)
{
    proxy.proxyData.type = ELightType::Directional;
}

List<ComponentProperty> ost::DirectionalLightComponent::GeneratePropertySet()
{
    List<ComponentProperty> properties;
    properties.Add({"Color", TypeID::Get<Color>(), &GetProxy().proxyData.color});
    properties.Add({"Intensity", TypeID::Get<Float32>(), &GetProxy().proxyData.intensity});
    return properties;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------