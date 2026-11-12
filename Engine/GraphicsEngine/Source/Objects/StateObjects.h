// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "RHI/RHIMinimal.h"

// ------------------------------------------------------------

namespace ost
{
    template <typename RHIType>
    struct StateObj
    {
        friend class RenderHardwareInterface;

        StateObj();
        StateObj(const StateObj&);
        StateObj(StateObj&&) noexcept;
        ~StateObj();

        StateObj& operator=(const StateObj&);
        StateObj& operator=(StateObj&&) noexcept;

        operator bool() const;

    private:
        ComPtr<RHIType> _resource;
    };

    using BlendState = StateObj<RHIBlendState>;
    using DepthStencilState = StateObj<RHIDepthStencilState>;

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------