#include "DXModel.h"
#include "DXHandling.h"

// ------------------------------------------------------------

ost::CDXModel& ost::CDXModel::AddVertex( const Vector4f& aVertPos, const SColor& aVertColor )
{
    _vertices.push_back( { aVertPos, aVertColor } );
    return *this;
}

void ost::CDXModel::InitializeResource()
{
    D3D11_SUBRESOURCE_DATA vertDescData = {};
    ZeroMemory( &vertDescData, sizeof( vertDescData ) );
    vertDescData.pSysMem = _vertices.data();
    
    D3D11_BUFFER_DESC vertDesc = {};
    ZeroMemory( &vertDesc, sizeof( vertDesc ) );
    vertDesc.Usage = D3D11_USAGE_IMMUTABLE;
    vertDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertDesc.ByteWidth = sizeof( SVertex_Pos4_Col4 ) * static_cast<UINT>(_vertices.size());
    vertDesc.CPUAccessFlags = 0;
    vertDesc.MiscFlags = 0;
    vertDesc.StructureByteStride = 0;
    
    OST_ASSERT( dx::Device->CreateBuffer( &vertDesc, &vertDescData, &_dxVertexBuffer ) == S_OK, "Create buffer successful" );
}


void ost::CDXModel::Render()
{
    dx::DeviceContext->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST );

    Uint32 stride = sizeof( SVertex_Pos4_Col4 );
    Uint32 offset = 0;
    dx::DeviceContext->IASetVertexBuffers( 0, 1, &_dxVertexBuffer, &stride, &offset );

    dx::DeviceContext->Draw( static_cast<UINT>(_vertices.size()), 0 );

}
    // ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
