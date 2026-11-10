// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Graphics/Material/MaterialClass.h"

#include "Engine/Graphics/Material/MaterialInstance.h"

#include <Utility/Assert.h>

using namespace ost;

// ------------------------------------------------------------

ost::MaterialClass::MaterialClass()
    : _litMode{EMaterialLitMode::Unset}
    , _domain{EMaterialDomain::Unset}
    , _instances{}
{
}

ost::MaterialClass::MaterialClass(MaterialClass&& materialClass) noexcept
    : _litMode{materialClass._litMode}
    , _domain{materialClass._domain}
    , _instances{std::move(materialClass._instances)}
{
    materialClass._litMode = EMaterialLitMode::Unset;
    materialClass._domain = EMaterialDomain::Unset;
    materialClass._instances.Clear();

    for (MaterialInstance& instance : _instances)
    {
        instance.SetClass(this);
    }
}

MaterialClass& ost::MaterialClass::operator=(MaterialClass&& materialClass) noexcept
{
    _litMode = materialClass._litMode;
    _domain = materialClass._domain;
    _instances = std::move(materialClass._instances);

    materialClass = MaterialClass{};

    for (MaterialInstance& instance : _instances)
    {
        instance.SetClass(this);
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
// ------------------------------------------------------------
// ------------------------------------------------------------