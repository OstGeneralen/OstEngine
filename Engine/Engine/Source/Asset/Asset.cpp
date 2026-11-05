// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Asset/Asset.h"

#include <Utility/Assert.h>

// ------------------------------------------------------------

ost::Asset::Asset(Asset&& asset) noexcept
    : _references{asset._references}
{
    asset._references = 0;
}

ost::Asset& ost::Asset::operator=(Asset&& asset) noexcept
{
    _references = asset._references;
    asset._references = 0;
    return *this;
}

// ------------------------------------------------------------

void ost::Asset::AddReference()
{
    _references++;
}

void ost::Asset::ReleaseReference()
{
    OST_ASSERT(_references > 0, "Cannot release more references than there are to any given asset");
    _references--;
}

SizeType ost::Asset::GetRefCount() const
{
    return _references;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------