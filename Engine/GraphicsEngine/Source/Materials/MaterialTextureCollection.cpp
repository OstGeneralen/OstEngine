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
        _textureSlotMask = _textureSlotMask | (1 << static_cast<Uint32>(desc.textureType));
        _textureNameToSlot.Insert(desc.name, desc.textureType);
    }
}

// ------------------------------------------------------------

bool MaterialTextureCollection::HasTexture(EMaterialTexture textureSlot) const
{
    return (_textureSlotMask & (1 << static_cast<Uint32>(textureSlot))) != 0;
}

// ------------------------------------------------------------

void MaterialTextureCollection::SetTexture(const std::string& name, HTexture texture)
{
    if (const EMaterialTexture* pSlot = _textureNameToSlot.TryGetValue(name))
    {
        SetTexture(*pSlot, texture);
    }
}

void MaterialTextureCollection::SetTexture(EMaterialTexture textureSlot, HTexture texture)
{
    if (HasTexture(textureSlot) == false)
    {
        return;
    }
    _textureHandles[static_cast<SizeType>(textureSlot)] = texture;
}

// ------------------------------------------------------------

HTexture MaterialTextureCollection::GetTexture(const std::string& name) const
{
    if (const EMaterialTexture* pSlot = _textureNameToSlot.TryGetValue(name))
    {
        return GetTexture(*pSlot);
    }
}

HTexture MaterialTextureCollection::GetTexture(EMaterialTexture textureSlot) const
{
    if (HasTexture(textureSlot) == false)
    {
        return {};
    }
    return _textureHandles[static_cast<SizeType>(textureSlot)];
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------