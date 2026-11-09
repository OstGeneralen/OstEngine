// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine/Resources/ShaderCompiler.h"

#include "RHI/RHIInternal.h"

#include <d3d11_1.h>
#include <d3dcompiler.h>

#include <OstLog.h>

#include <Container/Stack.h>
#include <Memory/Memory.h>
#include <Utility/File.h>

using namespace ost;

namespace fs = std::filesystem;

// ------------------------------------------------------------

auto ShaderCompileLog = Log::NewCategory("ShaderCompiler");

// ------------------------------------------------------------

namespace ost
{
    class ShaderIncludeHandler : public ID3DInclude
    {
    public:
        ShaderIncludeHandler(const fs::path& rootPath, const Map<std::string, fs::path>& remaps);

        HRESULT Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override;
        HRESULT Close(LPCVOID pData) override;

    private:
        Stack<fs::path> _includeStack;
        Map<std::string, fs::path> _includeRemaps;
    };
} // namespace ost

// ------------------------------------------------------------

List<Uint8> ost::ShaderCompiler::Compile(const ShaderSource& shaderSource)
{
    std::string shaderModel = "";
    switch (shaderSource.pipelineStage)
    {
    case EPipelineStage::VS:
        shaderModel = "vs_4_1";
        break;
    case EPipelineStage::PS:
        shaderModel = "ps_4_1";
        break;
    }

    ComPtr<ID3DBlob> shaderBlob;
    ComPtr<ID3DBlob> errorBlob;

    ShaderIncludeHandler includeHandler(shaderSource.includeRoot, shaderSource.includeRemapping);

    const HRESULT result = D3DCompile(shaderSource.sourceCode.GetData(),     // Code Data
                                      shaderSource.sourceCode.GetSize(),     // Code Size
                                      NULL,                                  // Source Name
                                      NULL,                                  // Defines
                                      &includeHandler,                       // Include manager
                                      shaderSource.shaderEntryPoint.c_str(), // Entry
                                      shaderModel.c_str(),                   // Shader Target
                                      D3DCOMPILE_DEBUG,                      // Flags 1
                                      0,                                     // Flags 2
                                      &shaderBlob,                           // Bytecode blob
                                      &errorBlob);

    if (FAILED(result))
    {
        const std::string errorMsg(static_cast<const char*>(errorBlob->GetBufferPointer()));
        Log::Error(ShaderCompileLog, "Failed to compile shader '{}': {}", shaderSource.shaderName, errorMsg);
        return {};
    }

    Log::Log(ShaderCompileLog, "Compiled shader '{}'", shaderSource.shaderName);

    List<Uint8> bytecode(shaderBlob->GetBufferSize());
    MemCopy(bytecode.GetData(), shaderBlob->GetBufferPointer(), bytecode.GetSize());
    return bytecode;
}

// ------------------------------------------------------------

ShaderIncludeHandler::ShaderIncludeHandler(const fs::path& rootPath, const Map<std::string, fs::path>& remaps)
    : _includeStack{}
    , _includeRemaps{remaps}
{
    fs::path includeRoot = fs::weakly_canonical(rootPath);
    if (fs::is_directory(includeRoot) == false)
    {
        includeRoot = includeRoot.parent_path();
    }
    _includeStack.Push(includeRoot);
}

HRESULT ShaderIncludeHandler::Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes)
{
    // Work out the include file path
    std::string includeName = pFileName;
    fs::path includePath = _includeStack.Top() / includeName;

    if (const fs::path* remapPath = _includeRemaps.TryGetValue(includeName))
    {
        includePath = *remapPath;
    }
    if (!fs::exists(includePath))
    {
        return S_FALSE;
    }

    _includeStack.Push(includePath.parent_path());

    // Now read the include file content
    SizeType fileSize = 0;
    (*ppData) = FileUtility::ReadFileToCharArray(includePath.string(), fileSize);
    (*pBytes) = static_cast<UINT>(fileSize);

    return S_OK;
}

HRESULT ost::ShaderIncludeHandler::Close(LPCVOID pData)
{
    delete[] pData;
    _includeStack.Pop();
    return S_OK;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------