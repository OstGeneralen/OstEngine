// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

// ------------------------------------------------------------
// The IRenderHardwareInterface exists purely to allow access
// to the low-level backend types in a generic way
// Most of the time you probably shouldn't use it as it makes
// your application code more connected with paltform specifics
// ------------------------------------------------------------

namespace ost
{
    enum class ERHIPlatform
    {
        Unknown,
        DX11,
        // Todo: Add here in future if supporting more platforms
    };

    class IRenderHardwareInterface
    {
    public:
        virtual ~IRenderHardwareInterface() = default;

        virtual ERHIPlatform GetBackendPlatform() const = 0;

        virtual const void* GetNativeDevice() const = 0;
        virtual const void* GetNativeContext() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------