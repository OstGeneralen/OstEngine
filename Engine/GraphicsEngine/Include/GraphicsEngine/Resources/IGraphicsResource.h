// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>
#include <string>

#include <Utility/TypedIntegerHandle.h>

// ------------------------------------------------------------

#define DECLARE_GFX_RESOURCE_HANDLE( HandleName ) using HandleName = TypedIntegerHandle<struct HNDType_##HandleName>;

// ------------------------------------------------------------

namespace ost
{
    struct IGraphicsResource
    {
        virtual const void* GetNativeResourcePtr() const = 0;
        virtual void SetDebugName(const std::string& name) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------