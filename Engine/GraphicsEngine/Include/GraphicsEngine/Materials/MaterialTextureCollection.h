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
    enum class EMaterialTexture
    {
        Albedo = 0,
        Normal,
        ORM,
        Custom1,
        Custom2,
        Custom3,
        Custom4,
        Custom5,
    };

    constexpr static SizeType MaterialTextureCount = 8;

    struct MaterialTextureDesc
    {
        std::string name;
        EMaterialTexture textureType;
    };

    class MaterialTextureCollection
    {
    public:
        MaterialTextureCollection();
        MaterialTextureCollection(const List<MaterialTextureDesc>& textureDescs);
        MaterialTextureCollection(const MaterialTextureCollection&);
        ~MaterialTextureCollection();

        bool HasTexture(EMaterialTexture texture) const;

        void SetTexture(const std::string& name, HTexture texture);
        void SetTexture(EMaterialTexture textureSlot, HTexture texture);
        
        HTexture GetTexture(const std::string& name) const;
        HTexture GetTexture(EMaterialTexture textureSlot) const;

    private:
        HTexture _textureHandles[8];
        Uint8 _textureSlotMask = 0;
        Map<std::string, EMaterialTexture> _textureNameToSlot;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------