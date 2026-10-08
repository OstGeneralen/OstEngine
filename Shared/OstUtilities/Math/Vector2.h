// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Math.h"

#include <DirectXMath.h>
#include <OstTypes.h>

// ------------------------------------------------------------

namespace ost
{
    template <typename T>
    struct Vector2Data
    {
        using DirectXType = void;
    };

    template <>
    struct Vector2Data<Float32>
    {
        using DirectXType = DirectX::XMFLOAT2;
    };

    template <>
    struct Vector2Data<Uint32>
    {
        using DirectXType = DirectX::XMUINT2;
    };

    template <>
    struct Vector2Data<Int32>
    {
        using DirectXType = DirectX::XMINT2;
    };

    template <typename T>
    class Vector2
    {
    public:
        using ThisType = Vector2<T>;

        // clang-format off
        union 
        {
            Vector2Data<T>::DirectXType dxType;
            struct { T X, Y; };
            T Arr[2];
        };
        // clang-format on

        Vector2()
            : X{0}
            , Y{0}
        {
        }
        Vector2(T x, T y)
            : X{x}
            , Y{y}
        {
        }
        Vector2(const Vector2& o)
            : dxType{o.dxType}
        {
        }

        inline ThisType operator+(const ThisType& rhs) const
        {
            return ThisType{X + rhs.X, Y + rhs.Y};
        }
        inline ThisType operator-(const ThisType& rhs) const
        {
            return ThisType{X - rhs.X, Y - rhs.Y};
        }
        inline ThisType operator*(const T scalar) const
        {
            return ThisType{X * scalar, Y * scalar};
        }
        inline ThisType operator/(const T scalar) const
        {
            return ThisType{X / scalar, Y / scalar};
        }

        inline ThisType& operator+=(const ThisType& rhs)
        {
            X += rhs.X;
            Y += rhs.Y;
            return *this;
        }
        inline ThisType& operator-=(const ThisType& rhs)
        {
            X -= rhs.X;
            Y -= rhs.Y;
            return *this;
        }
        inline ThisType& operator*=(const T scalar)
        {
            X *= scalar;
            Y *= scalar;
            return *this;
        }
        inline ThisType& operator/=(const T scalar)
        {
            X /= scalar;
            Y /= scalar;
            return *this;
        }

        bool operator==(const Vector2& rhs) const
        {
            return math::Equals(X, rhs.X) && math::Equals(Y, rhs.Y);
        }

        Vector2& operator=(const Vector2& rhs)
        {
            dxType = rhs.dxType;
            return *this;
        }

        Float32 Magnitude() const
        {
            Float32 mag = 0.0f;
            DirectX::XMStoreFloat(&mag, DirectX::XMVector2Length(DxTypeLoad(dxType)));
            return mag;
        }
        Float32 MagnitudeSq() const
        {
            Float32 magSq = 0.0f;
            DirectX::XMStoreFloat(&magSq, DirectX::XMVector2LengthSq(DxTypeLoad(dxType)));
            return magSq;
        }

        inline Vector2 GetNormalized() const
        {
            Vector2 norm;
            DxTypeStore(norm.dxType, DirectX::XMVector2Normalize(DxTypeLoad(dxType)));
            return norm;
        }

        inline Vector2& Normalize()
        {
            DxTypeStore(dxType, DirectX::XMVector2Normalize(DxTypeLoad(dxType)));
            return *this;
        }

        Float32 Dot(const Vector2& rhs) const
        {
            Float32 dot = 0.0f;
            DirectX::XMStoreFloat(&dot, DirectX::XMVector2Dot(DxTypeLoad(dxType), DxTypeLoad(rhs.dxType)));
            return dot;
        }

        template <typename T2>
        Vector2<T2> VectorCast() const
        {
            return Vector2<T2>{static_cast<T2>(X), static_cast<T2>(Y)};
        }

    private:
        inline static DirectX::XMVECTOR DxTypeLoad(const DirectX::XMFLOAT2& dxt)
        {
            return DirectX::XMLoadFloat2(&dxt);
        }
        inline static DirectX::XMVECTOR DxTypeLoad(const DirectX::XMINT2& dxt)
        {
            return DirectX::XMLoadSInt2(&dxt);
        }
        inline static DirectX::XMVECTOR DxTypeLoad(const DirectX::XMUINT2& dxt)
        {
            return DirectX::XMLoadUInt2(&dxt);
        }

        inline static void DxTypeStore(DirectX::XMFLOAT2& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreFloat2(&dxType, xmv);
        }
        inline static void DxTypeStore(DirectX::XMINT2& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreSInt2(&dxType, xmv);
        }
        inline static void DxTypeStore(DirectX::XMUINT2& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreUInt2(&dxType, xmv);
        }
    };

    using Vector2f = Vector2<Float32>;
    using Vector2u = Vector2<Uint32>;
    using Vector2i = Vector2<Int32>;
} // namespace ost