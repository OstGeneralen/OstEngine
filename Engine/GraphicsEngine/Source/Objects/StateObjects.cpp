// Kasper "OstGeneralen" Esbjornsson - 2026
#include "StateObjects.h"

#include "RHI/RHIInternal.h"

using namespace ost;

// ------------------------------------------------------------

StateObj<RHIBlendState>::StateObj() = default;
StateObj<RHIBlendState>::StateObj(const StateObj<RHIBlendState>&) = default;
StateObj<RHIBlendState>::StateObj(StateObj<RHIBlendState>&&) noexcept = default;
StateObj<RHIBlendState>::~StateObj() noexcept = default;

StateObj<RHIBlendState>& StateObj<RHIBlendState>::operator=(const StateObj<RHIBlendState>&) = default;
StateObj<RHIBlendState>& StateObj<RHIBlendState>::operator=(StateObj<RHIBlendState>&&) noexcept = default;

StateObj<RHIBlendState>::operator bool() const
{
    return _resource;
}

// ------------------------------------------------------------

StateObj<RHIDepthStencilState>::StateObj() = default;
StateObj<RHIDepthStencilState>::StateObj(const StateObj<RHIDepthStencilState>&) = default;
StateObj<RHIDepthStencilState>::StateObj(StateObj<RHIDepthStencilState>&&) noexcept = default;
StateObj<RHIDepthStencilState>::~StateObj() noexcept = default;

StateObj<RHIDepthStencilState>& StateObj<RHIDepthStencilState>::operator=(const StateObj<RHIDepthStencilState>&) = default;
StateObj<RHIDepthStencilState>& StateObj<RHIDepthStencilState>::operator=(StateObj<RHIDepthStencilState>&&) noexcept = default;

StateObj<RHIDepthStencilState>::operator bool() const
{
    return _resource;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------