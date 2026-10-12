// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RHIMinimal.h"
#include <string>

// ------------------------------------------------------------

namespace ost
{
    enum class ESamplerAddressMode
    {
        Wrap,
        Clamp,
    };

    enum class ESamplerType
    {
        Point,
        Bilinear,
        Trilinear,
    };

    struct TextureSampler
    {
        friend class RenderHardwareInterface;

        TextureSampler();
        TextureSampler(const TextureSampler&);
        ~TextureSampler();

        void SetDebugName(const std::string& name);
    private:
        ComPtr<RHISampler> _samplerState;
    };
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------