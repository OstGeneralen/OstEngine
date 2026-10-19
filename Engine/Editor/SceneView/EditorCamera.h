// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <Engine/World/Transform.h>

// ------------------------------------------------------------

namespace ost
{
    class EditorCamera
    {
    public:
        void Resize(const Vector2u& resolution);
        void Update();

    private:
        Transform _transform;
        Matrix4x4 _projection;
        Float32 _moveSpeed;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------