#include "DXRenderStateDescriptor.h"

#include "OSRFileReader.h"

#include <sstream>

ost::SDXInputElementDesc::SDXInputElementDesc()
{
    ZeroMemory( &D3DDesc, sizeof( D3DDesc ) );
}

void ost::SDXRenderStateDescriptor::InitFromFile( const std::string& aPath )
{
    _valid = COSRFileReader::TryReadFromFile( aPath, *this );
}

bool ost::SDXRenderStateDescriptor::IsValid() const
{
    return _valid;
}
