// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <OstEngine/ObjectSystem/Registration/ComponentTypeRegistration.h>
#include <unordered_map>

// ------------------------------------------------------------

namespace ost
{
	class CComponentTypeRegistry
	{
	public:
		template<TOstManagedType T> requires std::is_base_of_v<CComponent, T>
		void Register()
		{
			Register(SComponentTypeRegistration::Make<T>());
		}

		void Register(SComponentTypeRegistration registration);

		std::unordered_map<uint64, CManagedTypeContainerBase_Component*> MakeComponentsStorageInstance();
	private:
		std::vector<SComponentTypeRegistration> _registrations;
		uint64 _containersByteSize;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------