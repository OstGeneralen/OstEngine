// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Container/Map.h"
#include "Memory/UniquePtr.h"
#include "Utility/TypeID.h"

#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{

    class ServiceLocator
    {
    public:
        void RegisterManaged(TypeID registerType, UniquePtr<void>&& servicePtr);
        void RegisterUnmanaged(TypeID serviceType, void* pService);
        void Unregister(TypeID serviceType);
        void* Get(TypeID registerType);
        const void* Get(TypeID registerType) const;

        template <typename T>
        void RegisterManaged(UniquePtr<T>&& ptr)
        {
            Register(TypeID::Get<T>(), std::move(ptr));
        }

        template <typename T>
        void RegisterUnmanaged(T* ptr)
        {
            RegisterUnmanaged(TypeID::Get<T>(), ptr);
        }

        template <typename T>
        void Unregister()
        {
            Unregister(TypeID::Get<T>());
        }

        template <typename T>
        T* Get()
        {
            return static_cast<T*>(Get(TypeID::Get<T>()));
        }

        template <typename T>
        const T* Get() const
        {
            return static_cast<const T*>(Get(TypeID::Get<T>()));
        }

        template <typename T>
        T& GetRequired()
        {
            return *Get<T>();
        }

        template <typename T>
        const T& GetRequired() const
        {
            return *Get<T>();
        }

    private:
        struct ServiceRegistration
        {
            ServiceRegistration() = default;
            ServiceRegistration(ServiceRegistration&&) noexcept = default;
            ServiceRegistration& operator=(ServiceRegistration&&) noexcept = default;

            UniquePtr<void> pOwned;   // Only valid if owned == true
            void* pUnowned = nullptr; // Only valid if owned == false
            bool owned = false;       // true means the locator owns this service lifetime
        };

        Map<TypeID, ServiceRegistration> _registry;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------