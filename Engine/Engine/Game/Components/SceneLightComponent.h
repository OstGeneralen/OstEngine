// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Game/Component.h"

#include <Math/Color.h>
#include <Math/Vector3.h>

// ------------------------------------------------------------

namespace ost
{
    class SceneLightComponent : public Component
    {
    public:
        SceneLightComponent(Actor& owner)
            : Component{owner}
        {
        }

        void SetAmbientColor(const Color& ambientColor)
        {
            _ambientColor = ambientColor;
        }

        void SetSunColor(const Color& sunColor)
        {
            _sunColor = sunColor;
        }

        const Color& GetSunColor() const
        {
            return _sunColor;
        }

        const Color& GetAmbientColor() const
        {
            return _ambientColor;
        }

    private:
        Color _sunColor = Color{1.0f, 0.9f, 0.9f, 1.0f};
        Color _ambientColor = Color{0.0f, 0.002f, 0.01f, 1.0f};
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------