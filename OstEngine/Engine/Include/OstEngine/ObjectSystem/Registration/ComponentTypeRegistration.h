// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/ManagedType/ManagedObjectType.h>
#include <OstEngine/ObjectSystem/ManagedType/ManagedTypeContainer.h>
#include <OstEngine/ObjectSystem/Component.h>

#include <functional>

// ------------------------------------------------------------

namespace ost
{
	struct SComponentTypeRegistration
	{
		template<TOstComponentType T>
		static SComponentTypeRegistration Make()
		{
			SComponentTypeRegistration registration;
			registration._typeID = T::ReflectionData::TypeUID;
			registration._typeName = T::ReflectionData::TypeName;
			registration._createTypeContainerFunc = [](){ return new TManagedTypeContainer<T>(); };
			registration._registrationByteSize = sizeof(TManagedTypeContainer<T>);
			return registration;
		}

	private:
		friend class CComponentTypeRegistry;

		uint64 _typeID;
		uint64 _registrationByteSize;
		std::string_view _typeName;
		std::function< CManagedTypeContainerBase_Component*() > _createTypeContainerFunc;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
