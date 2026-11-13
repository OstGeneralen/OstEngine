// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Interfaces/IPixelShader.h"
#include "RHI/RHIMinimal.h"

// ------------------------------------------------------------

namespace ost
{
    struct PixelShader : public IPixelShader
    {
        friend class RenderHardwareInterface;

        PixelShader();
        PixelShader(const PixelShader&);
        PixelShader(PixelShader&&) noexcept;
        ~PixelShader();

        PixelShader& operator=(const PixelShader&);
        PixelShader& operator=(PixelShader&&) noexcept;

        operator bool() const;

        // BEGIN IPixelShader
        EBlendMode GetBlendMode() const override final;
        SizeType GetTargetCount() const override final;
        // END IPixelShader

    private:
        EBlendMode _blendMode;
        SizeType _targetCount;
        ComPtr<RHIPixelShader> _shader;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------