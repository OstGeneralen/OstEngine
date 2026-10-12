// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/ObjectHandles.h"
#include "GraphicsEngine/Materials/IMaterialInstance.h"
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
        static inline LightCommand Directional(const Vector3f& direction, const Color& color)
        {
            return LightCommand{EType::Directional, Matrix4x4(), direction, color};
        }
        static inline LightCommand Ambient(const Color& color)
        {
            return LightCommand{EType::Ambient, Matrix4x4(), Vector3f(), color};
        }

        enum class EType
        {
            Directional,
            Ambient,
        } type;
        Matrix4x4 transform;
        Vector3f forward;
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

        virtual void SetView( const Matrix4x4& viewProjection, const Matrix4x4& viewInverse ) = 0;
        virtual void Push(ModelCommand&& cmd) = 0;
        virtual void Push(LightCommand&& cmd) = 0;
        virtual void Clear() = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------