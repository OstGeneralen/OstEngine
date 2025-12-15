#pragma once
#include <OstEngine/Types.h>

#include <vector>

// ------------------------------------------------------------

struct ID3D11Buffer;

namespace ost
{
    class CDXConstantBuffer
    {
    public:
        template <typename TCBufferStructure>
        void Initialize( const TCBufferStructure& aStructure )
        {
            static_assert( sizeof( TCBufferStructure ) % 16 == 0,
                           "Structure initializing Cbuffer must be aligned to 16 bytes" );
            Initialize( &aStructure, sizeof( TCBufferStructure ) );
        }

        template <typename TCBufferSTructure>
        void Update( const TCBufferSTructure& aStructure )
        {
            static_assert( sizeof( TCBufferSTructure ) % 16 == 0,
                           "Structure Cbuffer must be aligned to 16 bytes" );
            Update( &aStructure, sizeof( TCBufferSTructure ) );
        }

        ID3D11Buffer* GetDXResource() const;

    private:
        void Initialize( const void* aCBufferInitialValue, Uint32 aDataSize );
        void Update(const void* cBufferValue, Uint32 aDataSize);

        ID3D11Buffer* _dxBuffer;
    };

    // ------------------------------------------------------------
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------