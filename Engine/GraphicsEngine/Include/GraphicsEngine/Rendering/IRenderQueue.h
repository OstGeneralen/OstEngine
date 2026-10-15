// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/IMaterialInstance.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <Math/Color.h>
#include <Math/Matrix4x4.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

namespace ost
{
    struct ModelCommand
    {
        ModelCommand(HModel h, HMaterialInstance hMatInstance, const Matrix4x4& t)
            : hModel{h}
            , hMaterialInstance{hMatInstance}
            , transform{t}
        {
        }

        HModel hModel;
        HMaterialInstance hMaterialInstance;
        Matrix4x4 transform;
    };
    struct LightCommand
    {
        enum class EType
        {
            Directional,
            Ambient,
            Point,
        } type;
        Vector3f position;
        Vector3f forward;
        Float32 radius;
        Color color;
    };

    struct RenderView
    {
        Matrix4x4 viewProjection;
        Matrix4x4 viewInverse;
    };

    class IRenderQueue
    {
    public:
        virtual ~IRenderQueue() = default;

        virtual void SetView(const Matrix4x4& viewProjection, const Matrix4x4& viewInverse) = 0;
        virtual void Push(ModelCommand&& cmd) = 0;
        virtual void Push(LightCommand&& cmd) = 0;
        virtual void Clear() = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------