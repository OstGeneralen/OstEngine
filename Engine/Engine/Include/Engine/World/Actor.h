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
    class GameWorld;

    class Actor
    {
    public:
        Transform transform;

    public:
        Actor(GameWorld& gameWorld);

        const StringID& GetName() const;
        void SetName(const std::string& name);

        List<ActorComponent*> GetComponents();
        List<const ActorComponent*> GetComponents() const;

        ActorComponent& AddComponent(TypeID componentType, UniquePtr<ActorComponent>&& component);
        void RemoveComponent(TypeID componentType);
        ActorComponent* GetComponent(TypeID componentType);
        const ActorComponent* GetComponent(TypeID componentType) const;

        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args)
        {
            return static_cast<T&>(AddComponent(TypeID::Get<T>(), Ptr::NewUnique<T>(std::forward<TArgs>(args)...)));
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
        GameWorld& _gameWorld;
        Map<TypeID, UniquePtr<ActorComponent>> _components;
        StringID _name;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------