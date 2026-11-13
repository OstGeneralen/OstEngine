// Kasper "OstGeneralen" Esbjornsson - 2026
#include "TextureTable.h"

#include "RHI/RHIInternal.h"
#include "Texture.h"

using namespace ost;

// ------------------------------------------------------------

TextureBundle::TextureBundle() = default;
TextureBundle::TextureBundle(const TextureBundle&) = default;
TextureBundle::TextureBundle(TextureBundle&&) noexcept = default;
TextureBundle::~TextureBundle() = default;

TextureBundle& TextureBundle::operator=(const TextureBundle&) = default;
TextureBundle& TextureBundle::operator=(TextureBundle&&) noexcept = default;

// ------------------------------------------------------------

TextureBundle::TextureBundle(const List<const Texture*>& pTextures)
{
    _srvs.Reserve(pTextures.GetSize());

    for (auto pTex : pTextures)
    {
        _srvs.Add(pTex->_srv);
    }
}

// ------------------------------------------------------------

List<const RHIShaderResource*> ost::TextureBundle::GetSRVList() const
{
    List<const RHIShaderResource*> list(_srvs.GetSize());
    for (SizeType i = 0; i < list.GetSize(); ++i)
    {
        list[i] = _srvs[i].Get();
    }
    return list;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------