// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <OstTypes.h>
#include <string>

#include <Container/List.h>
#include <Container/Map.h>

// ------------------------------------------------------------

namespace ost
{
    constexpr static SizeType MaterialTextureCount = 8;

    struct MaterialTextureDesc
    {
        std::string name;
        Uint32 textureBindPoint;
    };

    class MaterialTextureCollection
    {
    public:
        MaterialTextureCollection();
        MaterialTextureCollection(const List<MaterialTextureDesc>& textureDescs);
        MaterialTextureCollection(const MaterialTextureCollection&);
        ~MaterialTextureCollection();

        bool HasTexture(Uint32 bindPoint) const;

        void SetTexture(const std::string& name, HTexture texture);
        void SetTexture(Uint32 bindPoint, HTexture texture);
        
        HTexture GetTexture(const std::string& name) const;
        HTexture GetTexture(Uint32 bindPoint) const;

    private:
        HTexture _textureHandles[8];
        Uint8 _textureSlotMask = 0;
        Map<std::string, Uint32> _textureNameToSlot;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------