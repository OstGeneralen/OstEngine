// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/Game/ObjectSystem/Component/ComponentsCore.h>
#include <OstEngine/Game/ObjectSystem/StableIndexedType.h>
#include <OstEngine/Game/ObjectSystem/Objects/GameObjectHandle.h>

#include <concepts>
#include <typeinfo>

// ------------------------------------------------------------

namespace ost
{
	class CComponent
	{
		STABLE_IDX_CLASS_TYPE
	public: // Virtual API
		virtual ~CComponent() = default;
		
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void Tick() {}

	public: // Fixed API
		CGameObject& GetOwner();
		const CGameObject& GetOwner() const;

		bool ShouldTick() const;
		void SetShouldTick(bool shouldTick);
	private:
		friend class CComponentRegistry;
		SGameObjectHandle _hObject;
		bool _shouldTick{true};
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------