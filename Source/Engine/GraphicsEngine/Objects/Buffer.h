// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/RHI/RHIMinimal.h"

// ------------------------------------------------------------

namespace ost
{
    struct Buffer
    {
        friend class RenderHardwareInterface;

        Buffer();
        Buffer(const Buffer&);
        ~Buffer();

    private:
        SizeType _allocSize;
        ComPtr<RHIBuffer> _buffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------