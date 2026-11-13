// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"

#include <OstTypes.h>
#include <string>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct VertexElement
    {
        VertexElement(const VertexElement&) = default;

        VertexElement(const std::string& name, EDataSize fmt)
            : format{fmt}
            , semantic{name}
        {
        }

        EDataSize format = EDataSize::Unorm;
        std::string semantic = "";
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------