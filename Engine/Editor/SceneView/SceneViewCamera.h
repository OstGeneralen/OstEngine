// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

#include <Math/Quaternion.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

namespace ost
{
    class IRenderer;
    class IRenderQueue;

    class SceneViewCamera
    {
    public:
        void Move(const Vector3f& offset);
        
        void LookLeftRight(Float32 lookDegrees);
        void LookUpDown(Float32 lookDegrees);

        void InjectToRenderQueue(IRenderQueue& renderQueue, IRenderer& renderer);

    private:
        Vector3f _position = {0, 0, 0};
        Quaternion _rotation = {};
        Vector2f _lookDegrees;
        };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------