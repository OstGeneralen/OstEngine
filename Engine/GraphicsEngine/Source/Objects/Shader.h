// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/IShader.h"
#include "RHI/RHIMinimal.h"

// ------------------------------------------------------------

namespace ost
{
    struct Shader : IShader
    {
        friend class RenderHardwareInterface;

        Shader();
        Shader(const Shader&);
        Shader(Shader&&) noexcept;
        ~Shader();

        Shader& operator=(const Shader&);
        Shader& operator=(Shader&&) noexcept;

        void SetDebugName(const std::string& name) const;

        // BEGIN IShader
        BufferView GetBytecode() const override;
        EPipelineStage GetPipelineStage() const override;
        // END IShader

    private:
        EPipelineStage _stage; // VS or PS
        ComPtr<RHIPixelShader> _ps;
        ComPtr<RHIVertexShader> _vs;
        List<Uint8> _bytecode;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------