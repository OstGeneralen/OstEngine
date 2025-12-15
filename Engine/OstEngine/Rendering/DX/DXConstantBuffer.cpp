#include "DXConstantBuffer.h"

#include <OstEngine/Rendering/DX/DXRenderContext.h>

constexpr static Uint32 ByteAlignment = 16u;

// ------------------------------------------------------------

void ost::CDXConstantBuffer::Initialize( const void* aCBufferInitialValue, Uint32 aDataSize )
{
    D3D11_BUFFER_DESC desc;
    ZeroMemory( &desc, sizeof( desc ) );
    desc.ByteWidth = aDataSize;
    desc.Usage = D3D11_USAGE_DYNAMIC;
    desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

    D3D11_SUBRESOURCE_DATA initData;
    ZeroMemory( &initData, sizeof( initData ) );
    initData.pSysMem = aCBufferInitialValue;

    dx::Device->CreateBuffer( &desc, &initData, &_dxBuffer );
}

// ------------------------------------------------------------

void ost::CDXConstantBuffer::Update( const void* cBufferValue, Uint32 aDataSize )
{
    D3D11_MAPPED_SUBRESOURCE res;
    ZeroMemory( &res, sizeof( res ) );

    dx::DeviceContext->Map( _dxBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &res );
    memcpy_s( res.pData, aDataSize, cBufferValue, aDataSize );
    dx::DeviceContext->Unmap( _dxBuffer, 0 );
}

// ------------------------------------------------------------

ID3D11Buffer* ost::CDXConstantBuffer::GetDXResource() const
{
    return _dxBuffer;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------