// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ComponentFactory.h"

#include "Engine/World/Component.h"

#include <OstLog.h>

using namespace ost;

auto ComponentFactoryLog = Log::NewCategory("ComponentFactory");

// ------------------------------------------------------------

void ComponentFactory::RegisterComponentType(const std::string& name, ComponentTypeRegistration registration)
{
    _createFunctions.Insert(registration.typeID, registration.buildFunc);

    ComponentTypeInfo typeInfo;
    typeInfo.typeId = registration.typeID;
    typeInfo.typeName = name;
    _typeInfoList.Add(typeInfo);

    Log::Log(ComponentFactoryLog, "Registered new component type '{}' (id: {})", name, static_cast<SizeType>(typeInfo.typeId));
}

void ost::ComponentFactory::UnregisterComponentType(TypeID componentType)
{
    _createFunctions.Remove(componentType);

    for (SizeType i = 0; i < _typeInfoList.GetSize(); ++i)
    {
        if (_typeInfoList[i].typeId == componentType)
        {
            _typeInfoList.Remove(i);
            break;
        }
    }
}

// ------------------------------------------------------------

const List<ComponentTypeInfo>& ost::ComponentFactory::GetRegisteredTypesInfo() const
{
    return _typeInfoList;
}

// ------------------------------------------------------------

UniquePtr<ActorComponent> ost::ComponentFactory::CreateComponentFromType(TypeID typeID)
{
    return UniquePtr<ActorComponent>(_createFunctions[typeID]());
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------