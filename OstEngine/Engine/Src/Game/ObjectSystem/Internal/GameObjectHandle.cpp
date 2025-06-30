// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/Game/ObjectSystem/Internal/GameObjectHandle.h>

#include <OstEngine/Game/ObjectSystem/ObjectSystem.h>

// ------------------------------------------------------------

ost::SGameObjectHandle::SGameObjectHandle(SStableIndex sIdx, CGameObjectSystem& sys)
	: _objectStableIndex{sIdx}
	, _owningSystem{&sys}
{
}

// ------------------------------------------------------------

ost::CGameObject& ost::SGameObjectHandle::GetObject()
{
	return _owningSystem->GetObject(*this);
}

// ------------------------------------------------------------

const ost::CGameObject& ost::SGameObjectHandle::GetObject() const
{
	return _owningSystem->GetObject(*this);
}

// ------------------------------------------------------------

bool ost::SGameObjectHandle::IsValid() const
{
	return _owningSystem != nullptr && _objectStableIndex.IsValid();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------