// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Container/Map.h>
#include <Memory/UniquePtr.h>
#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class ServiceLocator
    {
    public:
        template <typename T>
        void Register(UniquePtr<T>&& s)
        {
            _registry.Insert(TypeID::Get<T>(), std::move(s));
        }

        template <typename T>
        T* Get()
        {
            if (UniquePtr<void>* ppService = _registry.TryGetValue(TypeID::Get<T>()))
            {
                return  reinterpret_cast<T*>(ppService->Get());
            }
            return nullptr;
        }

    private:
        Map<TypeID, UniquePtr<void>> _registry;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------