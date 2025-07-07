// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/ObjectSystem/Component.h>
#include <OstEngine/ObjectSystem/GameObject.h>
#include <OstEngine/ObjectSystem/ISceneContent.h>


// ------------------------------------------------------------

ost::CGameObject& ost::CComponent::GetOwner()
{
	return _sceneContent->GetObject(_ownerObjectID);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------