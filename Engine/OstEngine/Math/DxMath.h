#pragma once
#include <OstEngine/Math/DxMath/DirectXMath.h>
#include <OstEngine/Types.h>

namespace ost
{
    template <typename T, Uint16 N>
    struct DxVecTypeUtility
    {
    };

    template<>
    struct DxVecTypeUtility<Float64, 2>
    {

    };

    template <>
    struct DxVecTypeUtility<Float64, 3>
    {
    };

    template <>
    struct DxVecTypeUtility<Float64, 4>
    {

    };

    template<>
    struct DxVecTypeUtility<Float32, 2>
    {
        using DxVecType = DirectX::XMFLOAT2;

        static DirectX::XMVECTOR ToXMVec( const DxVecType& vt )
        {
            return DirectX::XMLoadFloat2( &vt );
        }

        static void StoreSingle( Float32& c, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreFloat( &c, xmv );
        }

        static void Store( DxVecType& vt, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreFloat2( &vt, xmv );
        }
    };

    template <>
    struct DxVecTypeUtility<Int32, 2>
    {
        using DxVecType = DirectX::XMINT2;
        static DirectX::XMVECTOR ToXMVec( const DxVecType& vt )
        {
            return DirectX::XMLoadInt2( reinterpret_cast<const uint32_t*>( &vt ) );
        }

        static void StoreSingle( Int32& c, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreInt( reinterpret_cast<uint32_t*>( &c ), xmv );
        }

        static void Store( DxVecType& vt, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreInt2( reinterpret_cast<uint32_t*>( &vt ), xmv );
        }
    };

    template <>
    struct DxVecTypeUtility<Uint32, 2>
    {
        using DxVecType = DirectX::XMUINT2;

        static DirectX::XMVECTOR ToXMVec( const DxVecType& vt )
        {
            return DirectX::XMLoadUInt2( &vt );
        }

        static void StoreSingle( Uint32& c, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreInt( &c, xmv );
        }

        static void Store( DxVecType& vt, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreUInt2( &vt, xmv );
        }
    };

    template <>
    struct DxVecTypeUtility<Float32, 3>
    {
        using DxVecType = DirectX::XMFLOAT3;

        static DirectX::XMVECTOR ToXMVec( const DxVecType& vt )
        {
            return DirectX::XMLoadFloat3( &vt );
        }

        static void StoreSingle( Float32& c, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreFloat( &c, xmv );
        }

        static void Store( DxVecType& vt, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreFloat3( &vt, xmv );
        }
    };

    template <>
    struct DxVecTypeUtility<Int32, 3>
    {
        using DxVecType = DirectX::XMINT3;

        static DirectX::XMVECTOR ToXMVec( const DxVecType& vt )
        {
            return DirectX::XMLoadInt3( reinterpret_cast<const uint32_t*>( &vt ) );
        }

        static void StoreSingle( Int32& c, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreInt( reinterpret_cast<uint32_t*>( &c ), xmv );
        }

        static void Store( DxVecType& vt, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreInt3( reinterpret_cast<uint32_t*>( &vt ), xmv );
        }
    };

    template <>
    struct DxVecTypeUtility<Uint32, 3>
    {
        using DxVecType = DirectX::XMUINT3;

        static DirectX::XMVECTOR ToXMVec( const DxVecType& vt )
        {
            return DirectX::XMLoadUInt3( &vt );
        }

        static void StoreSingle( Uint32& c, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreInt( &c, xmv );
        }

        static void Store( DxVecType& vt, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreUInt3( &vt, xmv );
        }
    };

    template <>
    struct DxVecTypeUtility<Float32, 4>
    {
        using DxVecType = DirectX::XMFLOAT4;

        static DirectX::XMVECTOR ToXMVec( const DxVecType& vt )
        {
            return DirectX::XMLoadFloat4( &vt );
        }

        static void StoreSingle( Float32& c, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreFloat( &c, xmv );
        }

        static void Store( DxVecType& vt, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreFloat4( &vt, xmv );
        }
    };

    template <>
    struct DxVecTypeUtility<Int32, 4>
    {
        using DxVecType = DirectX::XMINT4;

        static DirectX::XMVECTOR ToXMVec( const DxVecType& vt )
        {
            return DirectX::XMLoadInt4( reinterpret_cast<const uint32_t*>( &vt ) );
        }

        static void StoreSingle( Int32& c, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreInt( reinterpret_cast<uint32_t*>( &c ), xmv );
        }

        static void Store( DxVecType& vt, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreInt4( reinterpret_cast<uint32_t*>( &vt ), xmv );
        }
    };

    template <>
    struct DxVecTypeUtility<Uint32, 4>
    {
        using DxVecType = DirectX::XMUINT4;

        static DirectX::XMVECTOR ToXMVec( const DxVecType& vt )
        {
            return DirectX::XMLoadUInt4( &vt );
        }

        static void StoreSingle( Uint32& c, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreInt( &c, xmv );
        }

        static void Store( DxVecType& vt, DirectX::XMVECTOR xmv )
        {
            DirectX::XMStoreUInt4( &vt, xmv );
        }
    };

} // namespace ost