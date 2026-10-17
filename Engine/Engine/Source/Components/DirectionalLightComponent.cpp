// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Components/DirectionalLightComponent.h"

#include "Engine/World/Actor.h"
#include "Engine/World/IComponentInitializer.h"
#include "Engine/World/SceneGraph.h"
#include "Engine/World/Transform.h"

using namespace ost;

// ------------------------------------------------------------

void ost::DirectionalLightComponent::InitializeLightType(LightRenderProxy& proxy)
{
    proxy.proxyData.type = ELightType::Directional;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------