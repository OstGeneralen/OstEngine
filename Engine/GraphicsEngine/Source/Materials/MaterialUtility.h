// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Rendering/RenderPipelineConstants.h"
#include "GraphicsEngine/Materials/MaterialTextureCollection.h"

// ------------------------------------------------------------

namespace ost
{
    constexpr inline ETextureSlot MaterialTextureToBindSlot( EMaterialTexture matTex )
    {
        switch (matTex)
        {
        // clang-format off
        case EMaterialTexture::Albedo: return ETextureSlot::Albedo;
        case EMaterialTexture::Normal: return ETextureSlot::Normal;
        case EMaterialTexture::ORM: return ETextureSlot::ORM;
        case EMaterialTexture::Custom1: return ETextureSlot::Material1;
        case EMaterialTexture::Custom2: return ETextureSlot::Material2;
        case EMaterialTexture::Custom3: return ETextureSlot::Material3;
        case EMaterialTexture::Custom4: return ETextureSlot::Material4;
        case EMaterialTexture::Custom5: return ETextureSlot::Material5;
        // clang-format on
        }

        return ETextureSlot::Albedo;
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------