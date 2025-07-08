// OstEngine - Copyright(c) 2025 Kasper Esbj�rnsson (MIT License)
#include <EngineComponentRegistration.h>

#include <OstEngine/Game/Core/TransformComponent.h>

using namespace ost;

// ------------------------------------------------------------

void Engine_RegisterCoreComponents(ost::CComponentTypeRegistry& registry)
{
	registry.Register<CTransformComponent>();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------