// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Math/Matrix4x4.h>
#include <Math/Vector2.h>

// ------------------------------------------------------------

namespace ost
{
    class IRenderQueue;

    class IRenderer
    {
    public:
        virtual ~IRenderer() = default;

        virtual void Resize(const Vector2f& newSize) = 0;
        
        virtual Float32 GetAspectRatio() const = 0;
        virtual const Vector2f& GetDimensions() const = 0;

        virtual void ExecuteCommands(const Matrix4x4& view, const IRenderQueue& queue) = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------