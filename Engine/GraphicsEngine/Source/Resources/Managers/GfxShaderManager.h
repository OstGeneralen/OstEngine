// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Managers/IGfxShaderManager.h"
#include "Resources/GfxShaders.h"

#include <Container/SlotMap.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    class GfxShaderManager : public IGfxShaderManager
    {
    public:
        GfxShaderManager(const RenderHardwareInterface& rhi);

    private:
        const RenderHardwareInterface& _rhi;

        SlotMap<HVertexShader> _vertexShaders;
        SlotMap<HVertexShader> _pixelShaders;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------