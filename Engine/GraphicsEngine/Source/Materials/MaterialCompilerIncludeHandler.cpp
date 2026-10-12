// Kasper "OstGeneralen" Esbjornsson - 2026
#include "MaterialCompilerIncludeHandler.h"

#include <Utility/File.h>

using namespace ost;

// ------------------------------------------------------------

MaterialCompilerIncludeHandler::MaterialCompilerIncludeHandler(const std::filesystem::path& defaultRoot, const std::filesystem::path& materialFilePath)
    : _includeRoot{defaultRoot}
    , _materialIncludeReroute{materialFilePath}
{
    if (std::filesystem::is_directory(defaultRoot))
    {
        _includeRootStack.push(defaultRoot);
    }
    else if (defaultRoot.has_parent_path())
    {
        _includeRootStack.push(defaultRoot.parent_path());
    }
    else
    {
        _includeRootStack.push(defaultRoot);
    }
}

// ------------------------------------------------------------

HRESULT ost::MaterialCompilerIncludeHandler::Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes)
{
    const std::string& fileName = pFileName;

    std::filesystem::path includePath = _includeRootStack.top() / pFileName;
    includePath = std::filesystem::weakly_canonical(includePath); // Resolve any ../

    if (fileName == "OstMaterial.hlsli")
    {
        // This header is the utility under your game files so we just ignore it
        (*ppData) = nullptr;
        (*pBytes) = 0;
        return S_OK;
    }

    const bool isMaterialInclude = fileName == "MaterialInclude";
    if (isMaterialInclude)
    {
        includePath = _materialIncludeReroute;
    }

    SizeType sourceCodeSize = 0;
    (*ppData) = FileUtility::ReadFileToCharArray(includePath.string(), sourceCodeSize);
    (*pBytes) = static_cast<UINT>(sourceCodeSize);

    if (sourceCodeSize == 0)
    {
        return S_FALSE;
    }

    _includeRootStack.push(_includeRootStack.top());

    return S_OK;
}

HRESULT ost::MaterialCompilerIncludeHandler::Close(LPCVOID pData)
{
    if (pData == nullptr)
    {
        return S_OK;
    }

    _includeRootStack.pop();
    const char* bufferPtr = static_cast<const char*>(pData);
    delete[] bufferPtr;
    return S_OK;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------