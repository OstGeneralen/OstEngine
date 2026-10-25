// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <GraphicsEngine/Materials/IMaterialInstance.h>
#include <GraphicsEngine/Resources/ObjectHandles.h>
#include <GraphicsEngine/Rendering/Lights.h>
#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    struct StaticMeshRenderProxy
    {
        Matrix4x4 transform;
        HMaterialInstance materialHandles[8];
        HModel hModel;
    };

    struct LightRenderProxy
    {
        LightData proxyData;
    };

    struct ViewRenderProxy
    {
        enum class EProjectionType
        {
            Unset,
            Perspective,
            Orthographic,
        } projectionType = EProjectionType::Unset;

        Float32 lValue; // For Perspective, this is vFoV, for ortho this is percentage of width
        Float32 rValue; // For Perspective this is unused, for ortho this is percentage of height

        Matrix4x4 transform;
    };

    using ProxyHandle = Uint64;

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------