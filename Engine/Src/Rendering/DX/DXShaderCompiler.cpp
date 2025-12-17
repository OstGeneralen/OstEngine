#include "DXShaderCompiler.h"

#include <OstEngine/OstEngineMinimal.h>
#include <OstEngine/Utility/StringUtility.h>

#include <filesystem>

#include <d3dcompiler.h>

#include <Src/Debug/EngineLogInstances.h>
#include <Src/Rendering/DX/DXHandling.h>

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
        ShaderCompileLog.Detail( "Error Message:");
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
    if (blob == nullptr)
    {
        return nullptr;
    }

    ID3D11VertexShader* shader;
    HRESULT result = Device->CreateVertexShader( blob->GetBufferPointer(), blob->GetBufferSize(), NULL, &shader );
    if (result == S_OK)
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

ost::CDXShaderCompiler::CDXShaderCompiler( const std::string& aShaderFilePath )
    : _shaderFilePath{ aShaderFilePath.begin(), aShaderFilePath.end() }
    , _errorMessage{}
    , _vertexShader{ nullptr }
    , _pixelShader{ nullptr }
    , _compiledType{ EDxShaderType::Invalid }
    , _shaderBlob{ nullptr }
    , _hasErrors{ false }
{
}

// ------------------------------------------------------------

ost::CDXShaderCompiler::~CDXShaderCompiler()
{
    if ( _shaderBlob != nullptr )
    {
        _shaderBlob->Release();
    }

    if ( _vertexShader != nullptr )
    {
        _vertexShader->Release();
    }
    if ( _pixelShader != nullptr )
    {
        _pixelShader->Release();
    }
}

// ------------------------------------------------------------

void ost::CDXShaderCompiler::CompileShader( const std::string& aEntry, EDxShaderType aType )
{
    UINT compileFlags = D3DCOMPILE_ENABLE_STRICTNESS;

#if _DEBUG
    compileFlags = compileFlags | D3DCOMPILE_DEBUG;
#endif

    std::string target = "";
    switch ( aType )
    {
    case ost::EDxShaderType::Vertex:
        target = "vs_5_0";
        RendererLog.BeginInfo( "Compiling Vertex Shader" );
        break;
    case ost::EDxShaderType::Pixel:
        target = "ps_5_0";
        RendererLog.BeginInfo( "Compiling Pixel Shader" );
        break;
    }

    RendererLog.Detail( "Shader File: {}", stringUtils::WStringToString( _shaderFilePath ) );
    RendererLog.Detail( "Entry Point: {}", aEntry );

    ID3DBlob* errorBlob;
    HRESULT result = D3DCompileFromFile( _shaderFilePath.c_str(), NULL, NULL, aEntry.c_str(), target.c_str(),
                                         compileFlags, 0, &_shaderBlob, &errorBlob );

    if ( result != S_OK )
    {
        _compiledType = EDxShaderType::Invalid;
        _hasErrors = true;

        RendererLog.BeginError( "Shader Compile Error" );
        RendererLog.Error( "{}", static_cast<char*>( errorBlob->GetBufferPointer() ) );
        RendererLog.EndScope(); // Error scope
        RendererLog.EndScope(); // Main Scope
        errorBlob->Release();
        return;
    }

    switch ( aType )
    {
    case ost::EDxShaderType::Vertex:
        result = dx::Device->CreateVertexShader( _shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), NULL,
                                                 &_vertexShader );
        break;
    case ost::EDxShaderType::Pixel:
        result = dx::Device->CreatePixelShader( _shaderBlob->GetBufferPointer(), _shaderBlob->GetBufferSize(), NULL,
                                                &_pixelShader );
        break;
    }

    if ( result != S_OK )
    {
        RendererLog.Error( "Failed to create the shader resource" );
        _hasErrors = true;
        _vertexShader = nullptr;
        _pixelShader = nullptr;
        _shaderBlob->Release();
    }

    RendererLog.Confirm( "Compile Successful" );
    RendererLog.EndScope();
    _compiledType = aType;
}

// ------------------------------------------------------------

bool ost::CDXShaderCompiler::HasErrors() const
{
    return _hasErrors;
}

// ------------------------------------------------------------

const std::string& ost::CDXShaderCompiler::GetErrorString() const
{
    return _errorMessage;
}

// ------------------------------------------------------------

ID3DBlob* ost::CDXShaderCompiler::GetBlob()
{
    return _shaderBlob;
}

// ------------------------------------------------------------

ID3D11VertexShader* ost::CDXShaderCompiler::GetVertexShader( bool aConsume )
{
    OST_ASSERT( _vertexShader != nullptr,
                "You must compile as vertex shader using this compiler before accessing as vertex shader" );

    ID3D11VertexShader* tmpShader = _vertexShader;
    if ( aConsume )
    {
        _vertexShader = nullptr;
    }
    return tmpShader;
}

// ------------------------------------------------------------

ID3D11PixelShader* ost::CDXShaderCompiler::GetPixelShader( bool aConsume )
{
    OST_ASSERT( _pixelShader != nullptr,
                "You must compile as pixel shader using this compiler before accessing as pixel shader" );

    ID3D11PixelShader* tmpShader = _pixelShader;
    if ( aConsume )
    {
        _pixelShader = nullptr;
    }

    return tmpShader;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------