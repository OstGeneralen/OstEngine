// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/IMaterial.h"
#include "Materials/Material.h"
#include "Objects/PipelineStateObject.h"
#include "RHI/RHIInternal.h"

#include <d3dcompiler.h>

#include <OstTypes.h>
#include <filesystem>

#include <Container/List.h>

// ------------------------------------------------------------

namespace ost
{
    struct CompiledMaterial
    {
        PipelineStateObjectDesc stateObjectDesc;
        List<MaterialProperty> materialProperties;
    };

    class MaterialCompiler
    {
    public:
        MaterialCompiler(const MaterialDesc& desc);

        const PipelineStateObjectDesc& GetCompiledPSODesc() const;
        const MaterialPropertiesDesc& GetCompiledPropertySet() const;
        const List<MaterialTextureDesc> GetCompiledTextureDescs() const;

        bool Compile();

    private:
        void ExtractProperties(const ComPtr<ID3DBlob>& from);

        std::filesystem::path _materialShaderPath;
        std::filesystem::path _domainShaderPath;

        PipelineStateObjectDesc _psoDesc;
        MaterialPropertiesDesc _materialProperties;
        Map<EMaterialTexture, MaterialTextureDesc> _textureDescs;

        ComPtr<ID3DBlob> _vsBytecode;
        ComPtr<ID3DBlob> _psBytecode;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------