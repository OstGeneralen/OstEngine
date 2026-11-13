// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Interfaces/IVertexShader.h"
#include "RHI/RHIMinimal.h"

// ------------------------------------------------------------

namespace ost
{
    struct VertexShader : public IVertexShader
    {
        friend class RenderHardwareInterface;

        VertexShader();
        VertexShader(const VertexShader&);
        VertexShader(VertexShader&&);
        ~VertexShader();

        VertexShader& operator=(const VertexShader&);
        VertexShader& operator=(VertexShader&&) noexcept;

        operator bool() const;

        // BEGIN IVertexShader
        EVertexType GetVertexType() const override;
        // END IVertexShader

    private:
        EVertexType _vertexType;
        ComPtr<RHIVertexShader> _shader;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------