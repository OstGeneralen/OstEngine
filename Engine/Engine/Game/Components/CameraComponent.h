// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Game/Component.h"

#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    class CameraComponent : public Component
    {
    public:
        CameraComponent(Actor& owner)
            : Component{owner}
        {
        }

        void MakePerspective(Float32 vFoV, Float32 aspectRatio, Float32 nearZ = 0.01f, Float32 farZ = 1000.0f)
        {
            _projectionMatrix = Matrix4x4::CreatePerspectiveProjection(vFoV, aspectRatio, nearZ, farZ);
        }

        void MakeOrthographic(Float32 width, Float32 height, Float32 nearZ = 0.01f, Float32 farZ = 1000.0f)
        {
            _projectionMatrix = Matrix4x4::CreateOrthographicsProjection(width, height, nearZ, farZ);
        }

        const Matrix4x4& GetProjectionMatrix() const
        {
            return _projectionMatrix;
        }

    private:
        Matrix4x4 _projectionMatrix;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------