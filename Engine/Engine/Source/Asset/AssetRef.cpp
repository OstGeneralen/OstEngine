// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Asset/AssetRef.h"

#include "Engine/Asset/Asset.h"

using namespace ost;

// ------------------------------------------------------------

AssetRefBase::AssetRefBase()
    : _pAsset{nullptr}
{
}

AssetRefBase::AssetRefBase(Asset* pAsset)
    : _pAsset{pAsset}
{
    if(_pAsset)
    {
        _pAsset->AddReference();
    }
}

AssetRefBase::AssetRefBase(const AssetRefBase& ref)
    : _pAsset{ref._pAsset}
{
    if (_pAsset)
    {
        _pAsset->AddReference();
    }
}

AssetRefBase::AssetRefBase(AssetRefBase&& ref) noexcept
    : _pAsset{ref._pAsset}
{
    ref._pAsset = nullptr;
}

AssetRefBase::~AssetRefBase()
{
    if (_pAsset)
    {
        _pAsset->ReleaseReference();
    }
    _pAsset = nullptr;
}

// ------------------------------------------------------------

AssetRefBase& AssetRefBase::operator=(const AssetRefBase& ref)
{
    if (_pAsset)
    {
        _pAsset->ReleaseReference();
    }

    _pAsset = ref._pAsset;

    if (_pAsset)
    {
        _pAsset->AddReference();
    }

    return *this;
}

AssetRefBase& AssetRefBase::operator=(AssetRefBase&& ref) noexcept
{
    if (_pAsset)
    {
        _pAsset->ReleaseReference();
    }

    _pAsset = ref._pAsset;
    ref._pAsset = nullptr;

    return *this;
}

AssetRefBase& ost::AssetRefBase::operator=(std::nullptr_t)
{
    if (_pAsset)
    {
        _pAsset->ReleaseReference();
    }

    _pAsset = nullptr;
    return *this;
}

// ------------------------------------------------------------

AssetRefBase::operator bool() const
{
    return _pAsset != nullptr;
}

// ------------------------------------------------------------

Asset* AssetRefBase::Get()
{
    return _pAsset;
}

const Asset* AssetRefBase::Get() const
{
    return _pAsset;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------