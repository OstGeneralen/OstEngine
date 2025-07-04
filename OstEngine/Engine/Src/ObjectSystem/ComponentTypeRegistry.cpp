// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/ObjectSystem/Registration/ComponentTypeRegistry.h>
#include <OstLog/OstLogger.h>
#include <new>

// ------------------------------------------------------------

OSTLOG_LOG_INSTANCE(ComponentRegistryLog);

// ------------------------------------------------------------

void ost::CComponentTypeRegistry::Register(SComponentTypeRegistration registration)
{
	_registrations.push_back(registration);
	_containersByteSize += registration._registrationByteSize;

	{
		auto s = ComponentRegistryLog.ScopedLog(OstLogLevel::Debug, "Component Type Registered");
		s.Log("Name: {}", registration._typeName);
		s.Log("Type ID: {}", registration._typeID);
		s.Log("Container size: {} byte(s)", registration._registrationByteSize);
	}
}

// ------------------------------------------------------------

std::unordered_map<ost::uint64, ost::CManagedTypeContainerBase_Component*> ost::CComponentTypeRegistry::MakeComponentsStorageInstance()
{
	std::unordered_map<uint64, CManagedTypeContainerBase_Component*> map;

	// For now, we're just newing these as if there's no tomorrow
	// Later we probably want to manage this in a slightly nicer way
	for (auto& reg : _registrations)
	{
		map[reg._typeID] = reg._createTypeContainerFunc();
	}

	return std::move(map);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
