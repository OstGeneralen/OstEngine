#include "OstEngine/Rendering/ShaderBundle.h"

#include "Src/Rendering/DX/DXHandling.h"
#include "Src/Rendering/DX/DXOstEngineDefaults.h"

// ------------------------------------------------------------

void ost::CShaderBundle::InitFromFile( const std::string& aPath )
{
    void* ilBufferStart = nullptr;
    Uint64 ilBufferSize = 0u;
    ID3DBlob* vsBlob;
    _vsPtr = dx::CompileVertexShaderFromFile( aPath, "vsMain", &vsBlob);
    _psPtr = dx::CompilePixelShaderFromFile( aPath, "psMain" );

    _ilPtr = dx::CreateInputLayout( vsBlob->GetBufferPointer(), vsBlob->GetBufferSize());
    vsBlob->Release();
}

// ------------------------------------------------------------

void ost::CShaderBundle::BeginUse()
{
    dx::DeviceContext->IASetInputLayout( _ilPtr.Get<ID3D11InputLayout>() );

    dx::DeviceContext->VSSetShader( _vsPtr.Get<ID3D11VertexShader>(), nullptr, 0 );
    dx::DeviceContext->PSSetShader( _psPtr.Get<ID3D11PixelShader>(), nullptr, 0 );
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------