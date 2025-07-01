// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/Internal/StableIndexedTypeContainer.h>
#include <OstEngine/ObjectSystem/Objects/GameObject.h>
#include <OstEngine/ObjectSystem/Internal/ComponentRegistry.h>

// ------------------------------------------------------------

namespace ost
{
	struct SGameObjectHandle;
	
	// ------------------------------------------------------------
	// System
	// ------------------------------------------------------------
	class CGameObjectSystem
	{
	public:
		CGameObjectSystem();

		SGameObjectHandle CreateObject();
		void DestroyObject(SGameObjectHandle& handle);
		
		CGameObject& GetObject(const SGameObjectHandle& h);
		const CGameObject& GetObject(const SGameObjectHandle& h) const;

		CComponentRegistry& ComponentsRegistry();
	private:
		TStableIndexedTypeContainer<CGameObject> _objects;
		CComponentRegistry _componentRegistry;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
