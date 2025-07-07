// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/ManagedType/ManagedObjectType.h>
#include <string_view>
#include <OstEngine/ObjectSystem/Reflection/ReflectedTypeUtility.h>

#define OST_COMPONENT(Type) public:										\
	constexpr static std::string_view OstCompReflection_Name = #Type;	\
	using ReflectionData = ost::TReflectionData<Type>;					\

namespace ost
{
	class CGameObject;
	class ISceneContent;

	class CComponent
	{
		OST_MANAGED_TYPE
	public:
		static constexpr uint64 StaticUID = string_hash::HashString_64("ComponentBase");

	public:
		CGameObject& GetOwner();

	private:
		friend CGameObject;
		ISceneContent* _sceneContent;
		uint32 _ownerObjectID;
	};

	template<typename T> concept TOstComponentType = TOstManagedType<T> && std::is_base_of_v<CComponent, T>;
}