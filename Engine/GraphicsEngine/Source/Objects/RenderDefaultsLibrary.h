// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;
    struct PipelineStateObject;
    struct Mesh;

    class RenderDefaultsLibrary
    {
    public:
        static void Initialize(const RenderHardwareInterface& rhi);

        static const Mesh& GetBlitMesh();
        static const PipelineStateObject& GetBlitPSO();
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------