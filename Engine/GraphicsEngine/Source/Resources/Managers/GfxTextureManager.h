// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Managers/IGfxTextureManager.h"
#include "Resources/GfxTextures.h"

#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GfxTextureManager : public IGfxTextureManager
    {
    public:
        GfxTextureManager(const RenderHardwareInterface& rhi);

        // BEGIN IGfxTextureManager
        HTexture CreateFromDesc(const std::string& name, const TextureDesc& desc) override;
        HTexture CreateCustom(const std::string& name, const Vector2u& dimensions, const List<RGBAColor32>& pixels) override;

        const ITexture* Get(HTexture hnd) const override;

        void Release(HTexture& hnd) override;
        // END IGfxTextureManager

    private:
        const RenderHardwareInterface& _rhi;

        SlotMap<HTexture> _textures;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------