// Kasper "OstGeneralen" Esbjornsson - 2026
#include "HLSLCompiler.h"

#include "RHI/RHIInternal.h"

#include <d3dcompiler.h>

#include <OstLog.h>
#include <filesystem>

#include <Container/Stack.h>
#include <Memory/Memory.h>
#include <Utility/File.h>

// ------------------------------------------------------------

auto HLSLCompileLog = Log::NewCategory("HLSLCompiler");

// ------------------------------------------------------------

class HLSLIncludeManager : public ID3DInclude
{
public:
    HLSLIncludeManager(const std::string& rootInclude);

    HRESULT Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override;
    HRESULT Close(LPCVOID pData) override;

private:
    ost::Stack<std::filesystem::path> _includeStack;
};

// ------------------------------------------------------------

ost::List<Uint8> ost::HLSLCompiler::Compile(const std::string& shaderName, EPipelineStage shaderStage, const List<Uint8>& code, const std::string& entry,
                                            const std::string& rootInclude)
{
    LPCSTR model;
    switch (shaderStage)
    {
    case EPipelineStage::VS:
        model = "vs_4_1";
        break;
    case EPipelineStage::PS:
        model = "vs_4_1";
        break;
    default:
        Log::Error(HLSLCompileLog, "Unable to compile shader {}. Unknown shader type!", shaderName);
        return {};
    }

    HLSLIncludeManager includeManager{rootInclude};

    ComPtr<ID3DBlob> shaderBlob;
    ComPtr<ID3DBlob> errorBlob;

    HRESULT compileResult = D3DCompile(code.GetData(), code.GetSize(), NULL, NULL, &includeManager, entry.c_str(), model, D3DCOMPILE_DEBUG, 0, &shaderBlob, &errorBlob);

    if (FAILED(compileResult))
    {
        Log::Error(HLSLCompileLog, "Failed to compile shader with reason: '{}'", std::string(static_cast<const char*>(errorBlob->GetBufferPointer())));
        return {};
    }

    List<Uint8> byteCode = List<Uint8>(shaderBlob->GetBufferSize());
    MemCopy(byteCode.GetData(), shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize());

    return byteCode;
}

// ------------------------------------------------------------
// Include Manager
// ------------------------------------------------------------

namespace fs = std::filesystem;

HLSLIncludeManager::HLSLIncludeManager(const std::string& rootInclude)
{
    const fs::path includePath = fs::weakly_canonical(rootInclude);
    if (fs::is_directory(includePath))
    {
        _includeStack.Push(includePath);
    }
    else
    {
        _includeStack.Push(includePath.parent_path());
    }
}

HRESULT HLSLIncludeManager::Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes)
{
    const fs::path includePath = (*_includeStack.Peek()) / pFileName;
    const fs::path rootDirectory = fs::weakly_canonical(includePath.parent_path());
    _includeStack.Push(rootDirectory);

    SizeType rdSize = 0;
    *ppData = ost::FileUtility::ReadFileToCharArray(includePath.string(), rdSize);
    *pBytes = static_cast<UINT>(rdSize);
    return S_OK;
}

HRESULT HLSLIncludeManager::Close(LPCVOID pData)
{
    const char* arrData = static_cast<const char*>(pData);
    delete[] arrData;
    _includeStack.Pop();
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------