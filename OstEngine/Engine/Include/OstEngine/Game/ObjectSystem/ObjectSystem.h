// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/Internal/StableIndexedTypeContainer.h>
#include <OstEngine/Game/ObjectSystem/GameObject.h>

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
		SGameObjectHandle CreateObject();
		void DestroyObject(SGameObjectHandle& handle);
		
		CGameObject& GetObject(const SGameObjectHandle& h);
		const CGameObject& GetObject(const SGameObjectHandle& h) const;

	private:
		TStableIndexedTypeContainer<CGameObject> _objects;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
