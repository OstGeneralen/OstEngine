// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;
    class GraphicsResourceManager;
    class MaterialInstance;
    class Material;
    struct Mesh;

    class RenderCommandContext
    {
    public:
        RenderCommandContext(const RenderHardwareInterface& renderHardwareInterface, const GraphicsResourceManager& gfxResourceManager)
            : RHI{renderHardwareInterface}
            , Resources{gfxResourceManager}
        {
        }

        const RenderHardwareInterface& RHI;
        const GraphicsResourceManager& Resources;

        const Mesh* pCurrentMesh = nullptr;
        const Material* pCurrentMaterial = nullptr;
        const MaterialInstance* pCurrentMaterianInstance = nullptr;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------