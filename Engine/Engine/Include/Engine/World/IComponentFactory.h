// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <string>

#include <Container/List.h>
#include <Container/Map.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class Actor;
    class ActorComponent;

    typedef ActorComponent* (*ComponentCreateFunc)();

    // ------------------------------------------------------------

    struct ComponentTypeRegistration
    {
        friend class ComponentFactory; // NOT the interface, the backend impl

        template <typename T>
        static ComponentTypeRegistration MakeForT()
        {
            ComponentTypeRegistration reg;
            reg.typeID = TypeID::Get<T>();
            reg.buildFunc = &ComponentCreate<T>;
            return reg;
        }

    private:
        template<typename T>
        static ActorComponent* ComponentCreate()
        {
            return new T();
        }

        TypeID typeID;
        ComponentCreateFunc buildFunc;
    };

    // ------------------------------------------------------------

    struct ComponentTypeInfo
    {
        TypeID typeId;
        std::string typeName;
    };

    // ------------------------------------------------------------

    class IComponentFactory
    {
    public:
        virtual void RegisterComponentType(const std::string& name, ComponentTypeRegistration typeRegistration) = 0;
        virtual void UnregisterComponentType(TypeID componentType) = 0;

        virtual const List<ComponentTypeInfo>& GetRegisteredTypesInfo() const = 0;

        virtual const std::string& GetTypeName( TypeID componentType ) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------