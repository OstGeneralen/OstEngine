// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RHIMinimal.h"

// Descriptors
#include "GraphicsEngine/Resources/Descriptors/BufferDesc.h"
#include "GraphicsEngine/Resources/Descriptors/TextureDesc.h"

// Resources
#include "Resources/GfxBuffers.h"
#include "Resources/GfxShaders.h"
#include "Resources/GfxTextures.h"

// ------------------------------------------------------------

namespace ost
{
    class RHIFactory
    {
    public:
        void Initialize(ComPtr<RHIDevice> device);

        
    private:
        ComPtr<RHIDevice> _device;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------