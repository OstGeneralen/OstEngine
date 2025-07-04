// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/ObjectSystem/Scene.h>
#include <OstEngine/Game/Core/TransformComponent.h>
#include <OstLog/OstLogger.h>

#include <format>

// ------------------------------------------------------------

namespace
{
	template<typename ... TFmt>
	std::string FormatObjectName(std::string_view str, TFmt&& ... args)
	{
		return std::vformat(str, std::make_format_args(args...));
	}
}

// ------------------------------------------------------------

OSTLOG_LOG_INSTANCE(SceneLog);

// ------------------------------------------------------------

ost::CScene::CScene(CComponentTypeRegistry& registry)
	: _objects{}
	, _componentLists(std::move(registry.MakeComponentsStorageInstance()))
{
}

// ------------------------------------------------------------

ost::TPtr<ost::CGameObject> ost::CScene::CreateObject(std::string_view objectName)
{
	ost::TPtr<ost::CGameObject> objectPtr = _objects.Emplace();

	objectPtr->FinishCreate(this, Internal_GetMOD().GetStableIndex(), objectName.empty() ? ::FormatObjectName("GameObject{}", objectPtr->Internal_GetMOD().GetStableIndex()) : objectName);
	
	objectPtr->AddComponent<CTransformComponent>();

	{
		auto s = SceneLog.ScopedLog(OstLogLevel::Debug, "Created new object");
		s.Log("Name: {}", objectPtr->_name);
		s.Log("ID: {}", objectPtr->GetObjectID());
	}

	return objectPtr;
}

// ------------------------------------------------------------

void ost::CScene::Tick()
{
	for (auto& compTypeList : _componentLists)
	{
		compTypeList.second->TickAll();
	}
}

// ------------------------------------------------------------

ost::CGameObject& ost::CScene::GetObject(uint32 objectStableIndex)
{
	return _objects.Get(objectStableIndex);
}

// ------------------------------------------------------------

ost::uint32 ost::CScene::NewComponent(uint64 typeID)
{
	return GetContainerForComponentType(typeID)->NewComponent().Internal_GetMOD().GetStableIndex();
}

// ------------------------------------------------------------

ost::CComponent& ost::CScene::GetComponent(uint64 typeID, uint32 stableIndex)
{
	return GetContainerForComponentType(typeID)->GetBase(stableIndex);
}

// ------------------------------------------------------------

ost::CManagedTypeContainerBase_Component* ost::CScene::GetContainerForComponentType(uint64 componentTypeID)
{
	return _componentLists.at(componentTypeID);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------