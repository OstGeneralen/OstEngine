// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/IComponentFactory.h"

#include <Memory/UniquePtr.h>
#include <Container/Map.h>

// ------------------------------------------------------------

namespace ost
{
    class ActorComponent;

    class ComponentFactory : public IComponentFactory
    {
    public:
        // BEGIN IComponentFactory
        void RegisterComponentType(const std::string& name, ComponentTypeRegistration typeRegistration) override;
        void UnregisterComponentType(TypeID componentType) override;

        const List<ComponentTypeInfo>& GetRegisteredTypesInfo() const override;
        // END IComponentFactory

        UniquePtr<ActorComponent> CreateComponentFromType( TypeID typeID );

    private:
        Map<TypeID, ComponentCreateFunc> _createFunctions;
        Map<TypeID, std::string> _componentNames;
        List<ComponentTypeInfo> _typeInfoList;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------