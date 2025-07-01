// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include <OstEngine/ObjectSystem/Internal/ComponentRegistry.h>

#include <OstEngine/ObjectSystem/Component/ComponentHandle.h>
#include <OstEngine/ObjectSystem/Objects/GameObjectHandle.h>
#include <OstEngine/ObjectSystem/Objects/GameObject.h>

#include <OstLog/OstLogger.h>

// ------------------------------------------------------------

OSTLOG_LOG_INSTANCE(CompsLog);

void ost::CComponentRegistry::FinalizeComponentTypeRegistration(ComponentTypeID_t tID, const char* cName)
{
	CompsLog.Log(OstLogLevel::Info, "COMPONENT REGISTRATION N: {} UID: {}", cName, tID);
}

// ------------------------------------------------------------

ost::CComponentContainerBase* ost::CComponentRegistry::GetRegistryComponentTypeContainer(ComponentTypeID_t cTypeId)
{
	auto it = _registry.find(cTypeId);
	if (it == _registry.end())
	{
		return nullptr;
	}
	return it->second.get();
}

// ------------------------------------------------------------

ost::CComponent& ost::CComponentRegistry::GetComponent(const SComponentHandle& h)
{
	return _registry.at(h._componentTypeID)->GetComponent(h._componentStableIndex);
}

// ------------------------------------------------------------

ost::SComponentHandle ost::CComponentRegistry::GenerateComponentHandle(SStableIndex stableId, ComponentTypeID_t ctId)
{
	return SComponentHandle(stableId, ctId, *this);
}

// ------------------------------------------------------------

void ost::CComponentRegistry::TickComponents()
{
	for (auto& it : _registry)
	{
		CComponentContainerBase& compTypeContainer = *(it.second);

		for (uint64 compDenseIndex = 0; compDenseIndex < compTypeContainer.DenseComponentCount(); ++compDenseIndex)
		{
			compTypeContainer.ComponentAtDenseIndex(compDenseIndex).Tick();
		}
	}
}

// ------------------------------------------------------------

void ost::CComponentRegistry::DestroyComponent(ost::SComponentHandle& h)
{
	_registry.at(h._componentTypeID)->Remove(h._componentStableIndex);
	h.Invalidate();
}

// ------------------------------------------------------------

void ost::CComponentRegistry::AttachComponentToObject(SGameObjectHandle& hObject, const SComponentHandle& hComp, CComponent& compInstance)
{
	hObject.GetObject()._components.push_back(hComp);	// Add component to game object list of component handles
	compInstance._hObject = hObject;					// Set component instance handle to owner object
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------