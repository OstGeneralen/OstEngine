// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ServiceLocator.h"

using namespace ost;

// ------------------------------------------------------------

void ServiceLocator::Register(TypeID serviceType, UniquePtr<void>&& servicePtr)
{
    _registry.Insert(serviceType, std::move(servicePtr));
}

void ServiceLocator::Unregister(TypeID serviceType)
{
    _registry.Remove(serviceType);
}

// ------------------------------------------------------------

void* ServiceLocator::Get(TypeID serviceType)
{
    return _registry[serviceType].Get();
}

const void* ServiceLocator::Get(TypeID serviceType) const
{
    return _registry[serviceType].Get();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------