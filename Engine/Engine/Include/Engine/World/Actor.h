// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/World/Component.h"
#include "Engine/World/Transform.h"

#include <Container/List.h>
#include <Container/Map.h>
#include <Memory/UniquePtr.h>
#include <Utility/StringID.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class Scene;
    class IScene;

    struct ComponentData
    {
        TypeID componentTypeID;
        ActorComponent* pComponent;
    };

    class Actor
    {
    public:
        Transform transform;

    public:
        Actor(Scene& scene);
        ~Actor();

        IScene& GetScene();
        const IScene& GetScene() const;

        const StringID& GetName() const;
        void SetName(const std::string& name);

        List<ComponentData> GetComponents();

        ActorComponent& AddComponent(TypeID componentType);
        void RemoveComponent(TypeID componentType);
        void RemoveComponentImmediate( TypeID componentType );
        ActorComponent* GetComponent(TypeID componentType);
        const ActorComponent* GetComponent(TypeID componentType) const;

        template <typename T>
        T& AddComponent()
        {
            return static_cast<T&>(AddComponent(TypeID::Get<T>()));
        }

        template <typename T>
        void RemoveComponent()
        {
            RemoveComponent(TypeID::Get<T>());
        }

        template <typename T>
        T* GetComponent()
        {
            return static_cast<T*>(GetComponent(TypeID::Get<T>()));
        }

        template <typename T>
        const T* GetComponent() const
        {
            return static_cast<const T*>(GetComponent(TypeID::Get<T>()));
        }

    private:
        Scene& _scene;

        Map<TypeID, UniquePtr<ActorComponent>> _components;
        List<TypeID> _pendingRemoveComponentTypes;

        StringID _name;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------