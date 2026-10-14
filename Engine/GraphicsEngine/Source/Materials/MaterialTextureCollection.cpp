// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine/Materials/MaterialTextureCollection.h"

using namespace ost;

// ------------------------------------------------------------

MaterialTextureCollection::MaterialTextureCollection() = default;
MaterialTextureCollection::MaterialTextureCollection(const MaterialTextureCollection&) = default;
MaterialTextureCollection::~MaterialTextureCollection() = default;

MaterialTextureCollection::MaterialTextureCollection(const List<MaterialTextureDesc>& descs)
{
    for (const auto& desc : descs)
    {
        _textureSlotMask = _textureSlotMask | (1 << desc.textureBindPoint);
        _textureNameToSlot.Insert(desc.name, desc.textureBindPoint);
    }
}

// ------------------------------------------------------------

bool MaterialTextureCollection::HasTexture(Uint32 bindPoint) const
{
    return (_textureSlotMask & (1 << bindPoint)) != 0;
}

// ------------------------------------------------------------

void MaterialTextureCollection::SetTexture(const std::string& name, HTexture texture)
{
    if (const Uint32* pSlot = _textureNameToSlot.TryGetValue(name))
    {
        SetTexture(*pSlot, texture);
    }
}

void MaterialTextureCollection::SetTexture(Uint32 bindPoint, HTexture texture)
{
    if (HasTexture(bindPoint) == false)
    {
        return;
    }
    _textureHandles[bindPoint] = texture;
}

// ------------------------------------------------------------

HTexture MaterialTextureCollection::GetTexture(const std::string& name) const
{
    if (const Uint32* pSlot = _textureNameToSlot.TryGetValue(name))
    {
        return GetTexture(*pSlot);
    }
    return {};
}

HTexture MaterialTextureCollection::GetTexture(Uint32 bindPoint) const
{
    if (HasTexture(bindPoint) == false)
    {
        return {};
    }
    return _textureHandles[bindPoint];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------