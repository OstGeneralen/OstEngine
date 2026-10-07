// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Game/Actor.h"
#include "Engine/Game/Component.h"

#include <Math/Matrix4x4.h>

// ------------------------------------------------------------

namespace ost
{
    enum class EProjectionType
    {
        Perspective,
        Orthographic,
    };

    class CameraComponent : public Component
    {
    public:
        CameraComponent(Actor& owner)
            : Component{owner}
        {
        }

        void MakePerspective(Float32 vFoV, Float32 aspectRatio, Float32 nearZ = 0.01f, Float32 farZ = 1000.0f)
        {
            _projection = EProjectionType::Perspective;
            _perspective.vFoV = vFoV;
            _nearZ = nearZ;
            _farZ = farZ;
        }

        void MakeOrthographic(Float32 width, Float32 height, Float32 nearZ = 0.01f, Float32 farZ = 1000.0f)
        {
            _projection = EProjectionType::Orthographic;
            _orthographic = {width, height};
            _nearZ = nearZ;
            _farZ = farZ;
        }

        const Matrix4x4 GetViewMatrix(const Vector2f& renderDimensions) const
        {
            Matrix4x4 projectionMatrix;
            switch (_projection)
            {
            case EProjectionType::Perspective: {
                projectionMatrix = Matrix4x4::CreatePerspectiveProjection(_perspective.vFoV, renderDimensions.X / renderDimensions.Y, _nearZ, _farZ);
            }
            break;
            case EProjectionType::Orthographic: {
                projectionMatrix = Matrix4x4::CreateOrthographicsProjection(renderDimensions.X, renderDimensions.Y, _nearZ, _farZ);
            }
            }

            const Matrix4x4 viewMatrix = GetOwner().GetTransform().GetWorldTransform().GetInverse();

            return viewMatrix * projectionMatrix;
        }

    private:
        EProjectionType _projection;

        struct
        {
            Float32 vFoV = 0.0f;
        } _perspective;

        struct
        {
            Float32 width = 0.0f;
            Float32 height = 0.0f;
        } _orthographic;

        Float32 _nearZ = 0.0f;
        Float32 _farZ = 0.0f;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------