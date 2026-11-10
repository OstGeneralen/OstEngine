// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Graphics/Material/MaterialClass.h"

#include "Engine/Graphics/Material/MaterialInstance.h"

#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------

ost::MaterialClass::MaterialClass()
    : _litMode{EMaterialLitMode::Unset}
    , _domain{EMaterialDomain::Unset}
    , _instancePtrs{}
{
}

ost::MaterialClass::MaterialClass(MaterialClass&& materialClass) noexcept
    : _litMode{materialClass._litMode}
    , _domain{materialClass._domain}
    , _instancePtrs{std::move(materialClass._instancePtrs)}
{
    materialClass._litMode = EMaterialLitMode::Unset;
    materialClass._domain = EMaterialDomain::Unset;
    materialClass._instancePtrs.Clear();

    for (MaterialInstance* pInstance : _instancePtrs)
    {
        pInstance->UpdateClass(this);
    }
}

MaterialClass& ost::MaterialClass::operator=(MaterialClass&& materialClass) noexcept
{
    OST_ASSERT(_instancePtrs.IsEmpty(), "Cannot move assign if the target is in use!");

    _litMode = materialClass._litMode;
    materialClass._litMode = EMaterialLitMode::Unset;

    _domain = materialClass._domain;
    materialClass._domain = EMaterialDomain::Unset;

    _instancePtrs = std::move(materialClass._instancePtrs);
    materialClass._instancePtrs.Clear();

    for (MaterialInstance* pInstance : _instancePtrs)
    {
        pInstance->UpdateClass(this);
    }
}

// ------------------------------------------------------------

EVertexType ost::MaterialClass::GetVertexType() const
{
    switch (_domain)
    {
    case EMaterialDomain::SurfaceOpaque:
        return EVertexType::Static;
    case EMaterialDomain::PostProcess:
        return EVertexType::Blit;
    }

    return EVertexType::Position;
}

// ------------------------------------------------------------

void ost::MaterialClass::AddInstance(MaterialInstance& instance)
{
    _instancePtrs.Add(&instance);
}

void ost::MaterialClass::RemoveInstance(MaterialInstance& instance)
{
    for (SizeType i = 0; i < _instancePtrs.GetSize(); ++i)
    {
        if (_instancePtrs[i] == &instance)
        {
            _instancePtrs.Remove(i);
            return;
        }
    }
}

void ost::MaterialClass::UpdateInstancePtr(MaterialInstance* oldPtr, MaterialInstance* newPtr)
{
    for (MaterialInstance*& pInstance : _instancePtrs)
    {
        if (pInstance == oldPtr)
        {
            pInstance = newPtr;
            break;
        }
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------