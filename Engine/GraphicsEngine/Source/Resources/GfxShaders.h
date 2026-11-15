// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Shaders.h"
#include "RHI/RHIMinimal.h"
#include "Resources/GfxResourceHelper.h"

// ------------------------------------------------------------

namespace ost
{
    struct GfxVertexShader : public IVertexShader
    {
        DECLARE_GFX_RESOURCE_DEFAULTS(GfxVertexShader);

        GfxVertexShader(ComPtr<RHIVertexShader>&& vs, EVertexType vertType);

        const RHIVertexShader* GetRHIPtr() const;

        // BEGIN IVertexShader
        EVertexType GetVertexType() const override;
        // END IVertexShader

        // BEGIN IGraphicsResource
        const void* GetNativeResourcePtr() const override;
        void SetDebugName(const std::string& name) const override;
        // END IGraphicsResource

    private:
        ComPtr<RHIVertexShader> _shader;
        EVertexType _vertexType;
    };

    // ------------------------------------------------------------

    struct GfxPixelShader : public IPixelShader
    {
        DECLARE_GFX_RESOURCE_DEFAULTS(GfxPixelShader);

        GfxPixelShader(ComPtr<RHIPixelShader>&& ps, SizeType targetCount);

        const RHIPixelShader* GetRHIPtr() const;

        // BEGIN IVertexShader
        SizeType GetTargetCount() const override;
        // END IVertexShader

        // BEGIN IGraphicsResource
        const void* GetNativeResourcePtr() const override;
        void SetDebugName(const std::string& name) const override;
        // END IGraphicsResource
    private:
        ComPtr<RHIPixelShader> _shader;
        SizeType _targetCount = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------