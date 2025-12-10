#pragma once
#include <OstEngine/Math/Vectors.h>
#include <string>

namespace ost
{
    class CEngine;

    class IApplication
    {
    public:
        virtual void Load() = 0;
        virtual void Update() = 0;
        virtual void Render() = 0;
    };

} // namespace ost