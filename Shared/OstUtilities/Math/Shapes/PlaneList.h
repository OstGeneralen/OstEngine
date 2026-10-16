// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Container/List.h"
#include "Math/Shapes/Plane.h"
#include "Math/Shapes/Shape.h"

// ------------------------------------------------------------

namespace ost
{
    class PlaneList : public Shape3D
    {
    public:
        static PlaneList FromPlanes(std::initializer_list<Plane> planes)
        {
            PlaneList p;
            p._planes = List<Plane>(planes);
            return p;
        }

        void Add(const Plane& plane)
        {
            _planes.Add(plane);
        }

        // BEGIN Shape3D
        bool IsInside(const Vector3f& p) const override
        {
            for (const auto& plane : _planes)
            {
                if (!plane.IsInside(p))
                {
                    return false;
                }
            }
            return true;
        }
        // END Shape3D

    private:
        List<Plane> _planes;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------