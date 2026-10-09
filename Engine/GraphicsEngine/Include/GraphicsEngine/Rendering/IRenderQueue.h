// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <Math/Color.h>
#include <Math/Matrix4x4.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

namespace ost
{
    struct ModelCommand
    {
        ModelCommand(ModelHandle h, const Matrix4x4& t)
            : hModel{h}
            , transform{t}
        {
        }

        ModelHandle hModel;
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

    class IRenderQueue
    {
    public:
        virtual ~IRenderQueue() = default;

        virtual void SetView( const Matrix4x4& view ) = 0;
        virtual void Push(ModelCommand&& cmd) = 0;
        virtual void Push(LightCommand&& cmd) = 0;
        virtual void Clear() = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------