// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Game/Transform.h"

#include <Container/List.h>
#include <Container/Map.h>
#include <Container/Queue.h>
#include <Memory/UniquePtr.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class Scene;
    class Component;
    class EngineContext;

    class Actor
    {
    public:
        friend Scene;

        Actor(Scene& scene);
        ~Actor();

        Component* GetComponent(TypeID componentType);
        const Component* GetComponent(TypeID componentType) const;
        Component& AddComponent(TypeID componentType, UniquePtr<Component>&& component);

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

        template <typename T, typename... TArgs>
        T& AddComponent(TArgs&&... args)
        {
            return static_cast<T&>(AddComponent(TypeID::Get<T>(), Ptr::NewUnique<T>(*this, std::forward<TArgs>(args)...)));
        }

        void Tick(EngineContext& context);

        Actor* GetParent();
        void SetParent(Actor* parent);

        Scene& GetScene();

        Transform& GetTransform();
        const Transform& GetTransform() const;

    private:
        Transform _transform;

        Map<TypeID, UniquePtr<Component>> _components;
        Queue<Component*> _pendingLoadComponents;

        // Hierarchy
        List<Actor*> _children;
        Actor* _parent = nullptr;
        Scene* _scene;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------