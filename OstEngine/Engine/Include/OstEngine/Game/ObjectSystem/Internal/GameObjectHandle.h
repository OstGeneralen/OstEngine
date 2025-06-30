// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/Internal/StableIndex.h>

// ------------------------------------------------------------

namespace ost
{
	class CGameObject;
	class CGameObjectSystem;
	class CComponentRegistry;	
	
	struct SGameObjectHandle
	{
		SGameObjectHandle() = default;
		SGameObjectHandle(const SGameObjectHandle&) = default;
		SGameObjectHandle(SGameObjectHandle&&) noexcept = default;

		SGameObjectHandle& operator=(const SGameObjectHandle&) = default;
		SGameObjectHandle& operator=(SGameObjectHandle&&) noexcept = default;

		CGameObject& GetObject();
		const CGameObject& GetObject() const;

		bool IsValid() const;
	private:
		friend CGameObjectSystem;

		SGameObjectHandle(SStableIndex sIdx, CGameObjectSystem& sys);

		SStableIndex _objectStableIndex;
		CGameObjectSystem* _owningSystem;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
