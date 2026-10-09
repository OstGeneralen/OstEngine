// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RHIMinimal.h"
#include <string>

// ------------------------------------------------------------

namespace ost
{
    struct Buffer
    {
        friend class RenderHardwareInterface;

        Buffer();
        Buffer(const Buffer&);
        ~Buffer();

        void SetDebugName(const std::string& n) const;

    private:
        SizeType _allocSize;
        ComPtr<RHIBuffer> _buffer;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------