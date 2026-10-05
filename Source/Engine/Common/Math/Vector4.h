// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Math.h"
#include "Math/Vector3.h"

#include <OstTypes.h>

#include <DirectXMath.h>

// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    struct Vector4Data
    {
        using DirectXType = void;
    };

    template <>
    struct Vector4Data<Float32>
    {
        using DirectXType = DirectX::XMFLOAT4;
    };

    template <>
    struct Vector4Data<Uint32>
    {
        using DirectXType = DirectX::XMUINT4;
    };

    template <>
    struct Vector4Data<Int32>
    {
        using DirectXType = DirectX::XMINT4;
    };

    template <typename T>
    class Vector4
    {
    public:
        // clang-format off
        union 
        {
            Vector4Data<T>::DirectXType dxType;
            struct { Float32 X, Y, Z, W; };
            Float32 Arr[4];
        };
        // clang-format on

        Vector4()
            : X{0}
            , Y{0}
            , Z{0}
            , W{0}
        {
        }
        Vector4(T x, T y, T z, T w)
            : X{x}
            , Y{y}
            , Z{z}
            , W{w}
        {
        }
        Vector4(const Vector3<T>& v3, T w = 1)
            : X{v3.X}
            , Y{v3.Y}
            , Z{v3.Z}
            , W{w}
        {
        }

        Vector4(const Vector4& o)
            : dxType{o.dxType}
        {
        }

        inline Vector4 operator+(const Vector4& rhs) const
        {
            return Vector4{X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W};
        }
        inline Vector4 operator-(const Vector4& rhs) const
        {
            return Vector4{X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W};
        }
        inline Vector4 operator*(const T scalar) const
        {
            return Vector4{X * scalar, Y * scalar, Z * scalar, W * scalar};
        }
        inline Vector4 operator/(const T scalar) const
        {
            return Vector4{X / scalar, Y / scalar, Z / scalar, W / scalar};
        }

        inline Vector4& operator+=(const Vector4& rhs)
        {
            X += rhs.X;
            Y += rhs.Y;
            Z += rhs.Z;
            W += rhs.W;
            return *this;
        }
        inline Vector4& operator-=(const Vector4& rhs)
        {
            X -= rhs.X;
            Y -= rhs.Y;
            Z -= rhs.Z;
            W -= rhs.W;
            return *this;
        }
        inline Vector4& operator*=(const T scalar)
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
            W *= scalar;
            return *this;
        }
        inline Vector4& operator/=(const T scalar)
        {
            X /= scalar;
            Y /= scalar;
            Z /= scalar;
            W /= scalar;
            return *this;
        }

        inline bool operator==(const Vector4& rhs) const
        {
            return math::Equals(X, rhs.X) && math::Equals(Y, rhs.Y) && math::Equals(Z, rhs.Z) && math::Equals(W, rhs.W);
        }

        inline Vector4& operator=(const Vector4& rhs)
        {
            dxType = rhs.dxType;
            return *this;
        }

        inline Float32 Magnitude() const
        {
            Float32 mag = 0.0f;
            DirectX::XMStoreFloat(&mag, DirectX::XMVector4Length(DxTypeLoad(dxType)));
            return mag;
        }
        inline Float32 MagnitudeSq() const
        {
            Float32 magSq = 0.0f;
            DirectX::XMStoreFloat(&magSq, DirectX::XMVector4LengthSq(DxTypeLoad(dxType)));
            return magSq;
        }

        inline Float32 Dot(const Vector4& rhs) const
        {
            Float32 dot = 0.0f;
            DirectX::XMStoreFloat(&dot, DirectX::XMVector4Dot(DxTypeLoad(dxType), DxTypeLoad(rhs.dxType)));
            return dot;
        }
        inline Vector4 Cross(const Vector4& rhs) const
        {
            Vector4 crossed;
            crossed.DxTypeStore(crossed.dxType, DirectX::XMVector4Cross(DxTypeLoad(dxType), DxTypeLoad(rhs.dxType)));
            return crossed;
        }

        inline Vector4 GetNormalized() const
        {
            Vector3 norm;
            DxTypeStore(norm.dxType, DirectX::XMVector4Normalize(DxTypeLoad(dxType)));
            return norm;
        }
        inline Vector4& Normalize()
        {
            DxTypeStore(dxType, DirectX::XMVector4Normalize(DxTypeLoad(dxType)));
            return *this;
        }

        inline operator Vector3<T>() const
        {
            return Vector3<T>{X, Y, Z};
        }

        template <typename T2>
        Vector4<T2> VectorCast() const
        {
            return Vector4<T2>{static_cast<T2>(X), static_cast<T2>(Y), static_cast<T2>(Z), static_cast<T2>(W)};
        }

    private:
        inline DirectX::XMVECTOR DxTypeLoad(const DirectX::XMFLOAT4& dxt)
        {
            return DirectX::XMLoadFloat4(&dxt);
        }
        inline DirectX::XMVECTOR DxTypeLoad(const DirectX::XMINT4& dxt)
        {
            return DirectX::XMLoadSInt4(&dxt);
        }
        inline DirectX::XMVECTOR DxTypeLoad(const DirectX::XMUINT4& dxt)
        {
            return DirectX::XMLoadUInt4(&dxt);
        }

        inline void DxTypeStore(DirectX::XMFLOAT4& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreFloat4(&dxType, xmv);
        }
        inline void DxTypeStore(DirectX::XMINT4& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreSInt4(&dxType, xmv);
        }
        inline void DxTypeStore(DirectX::XMUINT4& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreUInt4(&dxType, xmv);
        }
    };

    using Vector4f = Vector4<Float32>;
    using Vector4u = Vector4<Uint32>;
    using Vector4i = Vector4<Int32>;

} // namespace ost