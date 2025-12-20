#pragma once
#include <OstEngine/Rendering/Camera.h>
#include <OstEngine/Utility/Timer.h>

namespace ost
{
    class IGame
    {
    public:
        virtual const CCamera& GetCamera() const = 0;
        virtual const Vector3f& GetSunDirection() const = 0;

        virtual void Load() = 0;
        virtual void Update( const ost::CTimer& aTimer ) = 0;
        virtual void Render() = 0;
    };

} // namespace ost