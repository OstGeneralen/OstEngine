// Kasper "OstGeneralen" Esbjornsson - 2026
#include "ShaderCompiler.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <dxgi.h>
#include <filesystem>

#include <Memory/Memory.h>


#include <iostream>

// ------------------------------------------------------------

ost::List<Uint8> ost::CompileShaderFromFile(const std::string& filePath, EPipelineStage targetStage)
{
    std::wstring pathWstr = std::wstring(filePath.begin(), filePath.end());

    static constexpr std::string_view psMain = "PSMain";
    static constexpr std::string_view vsMain = "VSMain";
    static constexpr std::string_view vsModel = "vs_4_1";
    static constexpr std::string_view psModel = "ps_4_1";

    std::string_view model = targetStage == EPipelineStage_VS ? vsModel.data() : psModel.data();
    std::string_view entry = targetStage == EPipelineStage_VS ? vsMain.data() : psMain.data();

    std::filesystem::path actualPath = filePath;
    actualPath = std::filesystem::absolute( actualPath );

    ComPtr<ID3DBlob> shaderBlob;
    ComPtr<ID3DBlob> errorBlob;
    HRESULT result = D3DCompileFromFile(actualPath.c_str(), NULL, D3D_COMPILE_STANDARD_FILE_INCLUDE, entry.data(), model.data(), D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);

    if(FAILED(result))
    {
        std::cerr << static_cast<const char*>( errorBlob->GetBufferPointer()) << std::endl;
    }

    List<Uint8> bytecode;
    bytecode.Resize(shaderBlob->GetBufferSize());

    MemCopy(bytecode.GetData(), shaderBlob->GetBufferPointer(), bytecode.GetSize());

    return bytecode;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------