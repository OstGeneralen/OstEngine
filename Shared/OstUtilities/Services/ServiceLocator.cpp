// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ServiceLocator.h"

using namespace ost;

// ------------------------------------------------------------

void ServiceLocator::RegisterManaged(TypeID serviceType, UniquePtr<void>&& servicePtr)
{
    ServiceRegistration registration;
    registration.owned = true;
    registration.pOwned = std::move(servicePtr);
    _registry.Insert(serviceType, std::move(registration));
}

void ServiceLocator::RegisterUnmanaged(TypeID serviceType, void* pService)
{
    ServiceRegistration registration;
    registration.owned = false;
    registration.pUnowned = pService;
    _registry.Insert(serviceType, std::move(registration));
}

void ServiceLocator::Unregister(TypeID serviceType)
{
    _registry.Remove(serviceType);
}

// ------------------------------------------------------------

void* ServiceLocator::Get(TypeID serviceType)
{
    auto& reg = _registry[serviceType];
    return reg.owned ? reg.pOwned.Get() : reg.pUnowned;
}

const void* ServiceLocator::Get(TypeID serviceType) const
{
    const auto& reg = _registry[serviceType];
    return reg.owned ? reg.pOwned.Get() : reg.pUnowned;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------