#include "OstEngine/Debug/Logging/LogInstance.h"
#include "Src/Rendering/DX/DXHandling.h"

#include <OstEngine/OstEngineMinimal.h>
#include <OstEngine/Utility/StringUtility.h>

#include <filesystem>

#include <d3dcompiler.h>

ost::log::CLogInstance ShaderCompileLog{ "ShaderCompile" };

// ------------------------------------------------------------
// DX Handling shader compile functions
// ------------------------------------------------------------

ID3DBlob* CompileShaderFromFile( const std::string& aPath, const std::string& aEntry, const std::string& aTarget )
{
    UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if _DEBUG
    compileFlags = compileFlags | D3DCOMPILE_DEBUG;
#endif

    auto logDetails = [&]() {
        ShaderCompileLog.Detail( "File: {}", aPath );
        ShaderCompileLog.Detail( "Entry: {}", aEntry );
        ShaderCompileLog.Detail( "Target: {}", aTarget );
    };

    std::wstring pathWide = ost::stringUtils::StringToWString( aPath );
    ID3DBlob* errorBlob;
    ID3DBlob* shaderBlob;
    HRESULT result = D3DCompileFromFile( pathWide.c_str(), NULL, NULL, aEntry.c_str(), aTarget.c_str(), compileFlags, 0,
                                         &shaderBlob, &errorBlob );

    if ( result != S_OK )
    {
        ShaderCompileLog.BeginError( "Shader Compile Error" );
        logDetails();
        ShaderCompileLog.Detail( "Error Message:" );
        ShaderCompileLog.Error( "{}", static_cast<char*>( errorBlob->GetBufferPointer() ) );
        ShaderCompileLog.EndScope(); // Error scope
        errorBlob->Release();
        return nullptr;
    }

    ShaderCompileLog.BeginConfirm( "Successfully Compiled Shader" );
    logDetails();
    ShaderCompileLog.EndScope();

    return shaderBlob;
}

// ------------------------------------------------------------

ID3D11VertexShader* ost::dx::CompileVertexShaderFromFile( const std::string& aPath, const std::string& aEntry,
                                                          void** outShaderBuffer, Uint64& outBufferSize )
{
    ID3DBlob* blob = CompileShaderFromFile( aPath, aEntry, "vs_5_0" );
    if ( blob == nullptr )
    {
        return nullptr;
    }

    ID3D11VertexShader* shader;
    HRESULT result = Device->CreateVertexShader( blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader );
    if ( result == S_OK )
    {
        ( *outShaderBuffer ) = blob->GetBufferPointer();
        outBufferSize = blob->GetBufferSize();
    }
    else
    {
        ShaderCompileLog.Error( "Failed to create shader resource for sucessfully compiled shader" );
    }

    blob->Release();
    return shader;
}

// ------------------------------------------------------------

ID3D11PixelShader* ost::dx::CompilePixelShaderFromFile( const std::string& aPath, const std::string& aEntry )
{
    ID3DBlob* blob = CompileShaderFromFile( aPath, aEntry, "vs_5_0" );
    if ( blob == nullptr )
    {
        return nullptr;
    }

    ID3D11PixelShader* shader;
    HRESULT result = Device->CreatePixelShader( blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader );
    if ( result != S_OK )
    {
        ShaderCompileLog.Error( "Failed to create shader resource for sucessfully compiled shader" );
    }

    blob->Release();
    return shader;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------