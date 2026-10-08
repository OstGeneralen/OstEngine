// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Math.h"
#include "Math/Vector2.h"

#include <OstTypes.h>

#include <DirectXMath.h>

// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    struct Vector3Data
    {
        using DirectXType = void;
    };

    template <>
    struct Vector3Data<Float32>
    {
        using DirectXType = DirectX::XMFLOAT3;
    };

    template <>
    struct Vector3Data<Uint32>
    {
        using DirectXType = DirectX::XMUINT3;
    };

    template <>
    struct Vector3Data<Int32>
    {
        using DirectXType = DirectX::XMINT3;
    };

    template <typename T>
    class Vector3
    {
    public:
        // clang-format off
        union 
        {
            Vector3Data<T>::DirectXType dxType;
            struct { Float32 X, Y, Z; };
            Float32 Arr[3];
        };
        // clang-format on

        Vector3()
            : X{0}
            , Y{0}
            , Z{0}
        {
        }
        Vector3(T x, T y, T z)
            : X{x}
            , Y{y}
            , Z{z}
        {
        }
        Vector3(const Vector2<T>& v2, T z = 0)
            : X{v2.X}
            , Y{v2.Y}
            , Z{z}
        {
        }

        Vector3(const Vector3& o)
            : dxType{o.dxType}
        {
        }

        inline Vector3 operator+(const Vector3& rhs) const
        {
            return Vector3{X + rhs.X, Y + rhs.Y, Z + rhs.Z};
        }
        inline Vector3 operator-(const Vector3& rhs) const
        {
            return Vector3{X - rhs.X, Y - rhs.Y, Z - rhs.Z};
        }
        inline Vector3 operator*(const T scalar) const
        {
            return Vector3{X * scalar, Y * scalar, Z * scalar};
        }
        inline Vector3 operator/(const T scalar) const
        {
            return Vector3{X / scalar, Y / scalar, Z / scalar};
        }

        inline Vector3& operator+=(const Vector3& rhs)
        {
            X += rhs.X;
            Y += rhs.Y;
            Z += rhs.Z;
            return *this;
        }
        inline Vector3& operator-=(const Vector3& rhs)
        {
            X -= rhs.X;
            Y -= rhs.Y;
            Z -= rhs.Z;
            return *this;
        }
        inline Vector3& operator*=(const T scalar)
        {
            X *= scalar;
            Y *= scalar;
            Z *= scalar;
            return *this;
        }
        inline Vector3& operator/=(const T scalar)
        {
            X /= scalar;
            Y /= scalar;
            Z /= scalar;
            return *this;
        }

        inline bool operator==(const Vector3& rhs) const
        {
            return math::Equals(X, rhs.X) && math::Equals(Y, rhs.Y) && math::Equals(Z, rhs.Z);
        }

        inline Vector3& operator=(const Vector3& rhs)
        {
            dxType = rhs.dxType;
            return *this;
        }

        inline Float32 Magnitude() const
        {
            Float32 mag = 0.0f;
            DirectX::XMStoreFloat(&mag, DirectX::XMVector3Length(DxTypeLoad(dxType)));
            return mag;
        }
        inline Float32 MagnitudeSq() const
        {
            Float32 magSq = 0.0f;
            DirectX::XMStoreFloat(&magSq, DirectX::XMVector3LengthSq(DxTypeLoad(dxType)));
            return magSq;
        }

        inline Vector3 GetNormalized() const
        {
            Vector3 norm = *this;
            norm.Normalize();
            return norm;
        }

        inline Vector3& Normalize()
        {
            DxTypeStore(dxType, DirectX::XMVector3Normalize(DxTypeLoad(dxType)));
            return *this;
        }

        inline Float32 Dot(const Vector3& rhs) const
        {
            Float32 dot = 0.0f;
            DirectX::XMStoreFloat(&dot, DirectX::XMVector3Dot(DxTypeLoad(dxType), DxTypeLoad(rhs.dxType)));
            return dot;
        }
        inline Vector3 Cross(const Vector3& rhs) const
        {
            Vector3 crossed;
            crossed.DxTypeStore(crossed.dxType, DirectX::XMVector3Cross(DxTypeLoad(dxType), DxTypeLoad(rhs.dxType)));
            return crossed;
        }

        inline operator Vector2<T>() const
        {
            return Vector2<T>{X, Y};
        }

        template <typename T2>
        Vector3<T2> VectorCast() const
        {
            return Vector3<T2>{static_cast<T2>(X), static_cast<T2>(Y), static_cast<T2>(Z)};
        }

    private:
        inline static DirectX::XMVECTOR DxTypeLoad(const DirectX::XMFLOAT3& dxt)
        {
            return DirectX::XMLoadFloat3(&dxt);
        }
        inline static DirectX::XMVECTOR DxTypeLoad(const DirectX::XMINT3& dxt)
        {
            return DirectX::XMLoadSInt3(&dxt);
        }
        inline static DirectX::XMVECTOR DxTypeLoad(const DirectX::XMUINT3& dxt)
        {
            return DirectX::XMLoadUInt3(&dxt);
        }

        inline void DxTypeStore(DirectX::XMFLOAT3& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreFloat3(&dxType, xmv);
        }
        inline void DxTypeStore(DirectX::XMINT3& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreSInt3(&dxType, xmv);
        }
        inline void DxTypeStore(DirectX::XMUINT3& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreUInt3(&dxType, xmv);
        }
    };

    using Vector3f = Vector3<Float32>;
    using Vector3u = Vector3<Uint32>;
    using Vector3i = Vector3<Int32>;
} // namespace ost