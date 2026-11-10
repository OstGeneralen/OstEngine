// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Graphics/Material/MaterialInstance.h"

#include "Engine/Graphics/Material/MaterialClass.h"

#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------

ost::MaterialInstance::MaterialInstance()
    : _pClass{nullptr}
{
}

ost::MaterialInstance::MaterialInstance(MaterialInstance&& other) noexcept
    : _pClass{other._pClass}
{
    other = MaterialInstance();

    _pClass->UpdateInstancePtr(&other, this);
}

ost::MaterialInstance::MaterialInstance(MaterialClass& materialClass)
    : _pClass{&materialClass}
{
}

// ------------------------------------------------------------

MaterialInstance& ost::MaterialInstance::operator=(MaterialInstance&& other) noexcept
{
    OST_ASSERT(_pClass == nullptr, "Cannot move assign when target is in use!");

    _pClass = other._pClass;
    other._pClass = nullptr;

    _pClass->UpdateInstancePtr(&other, this);
}

// ------------------------------------------------------------

const MaterialClass& ost::MaterialInstance::GetClass() const
{
    return *_pClass;
}

// ------------------------------------------------------------

void ost::MaterialInstance::UpdateClass(MaterialClass* newPtr)
{
    _pClass = newPtr;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------