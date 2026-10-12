// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <d3dcompiler.h>

#include <OstTypes.h>
#include <filesystem>
#include <stack>

#include <Container/Map.h>

// ------------------------------------------------------------

namespace ost
{
    class MaterialCompilerIncludeHandler : public ID3DInclude
    {
    public:
        MaterialCompilerIncludeHandler(const std::filesystem::path& defaultRoot, const std::filesystem::path& materialFilePath);

        HRESULT Open(D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID* ppData, UINT* pBytes) override;
        HRESULT Close(LPCVOID pData) override;

    private:
        std::filesystem::path _includeRoot;
        std::filesystem::path _materialIncludeReroute;
        std::stack<std::filesystem::path> _includeRootStack;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------