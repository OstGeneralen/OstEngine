#include "DXShaderCompiler.h"

#include <OstEngine/OstEngineMinimal.h>
#include <OstEngine/Debug/EngineLogInstances.h>
#include <OstEngine/Rendering/DX/DXHandling.h>

#include <d3dcompiler.h>

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

    RendererLog.Detail( "Shader File: {}", std::string( _shaderFilePath.begin(), _shaderFilePath.end() ) );
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