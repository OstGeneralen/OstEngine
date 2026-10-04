// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Math/Math.h"
#include "Math/Vector4.h"

#include <OstTypes.h>

#include <DirectXMath.h>

// ------------------------------------------------------------

namespace ost
{
    class Quaternion
    {
    public:
        // clang-format off
        union 
        {
            DirectX::XMFLOAT4 dxType;
            struct { Float32 X, Y, Z, W; };
            Float32 Arr[4];
        };
        // clang-format on

    public:
        static Quaternion FromRotationAxis(const Vector3f& axis, Float32 rad)
        {
            Quaternion created;
            DxTypeStore(created.dxType, DirectX::XMQuaternionRotationAxis(DirectX::XMLoadFloat3(&axis.dxType), rad));
            return created;
        }

    public:
        Quaternion()
            : X{0}
            , Y{0}
            , Z{0}
            , W{1}
        {
        }
        Quaternion(const Quaternion& rhs)
            : dxType{rhs.dxType}
        {
        }

        inline bool operator==(const Quaternion& rhs) const
        {
            return DirectX::XMQuaternionEqual(DxTypeLoad(dxType), DxTypeLoad(rhs.dxType));
        }

        inline Quaternion& operator=(const Quaternion& rhs)
        {
            dxType = rhs.dxType;
            return *this;
        }

        inline Quaternion operator*(const Quaternion& rhs) const
        {
            Quaternion result;
            DxTypeStore(result.dxType, DirectX::XMQuaternionMultiply(DxTypeLoad(dxType), DxTypeLoad(rhs.dxType)));
            return result;
        }
        inline Quaternion& operator*=(const Quaternion& rhs)
        {
            DxTypeStore(dxType, DirectX::XMQuaternionMultiply(DxTypeLoad(dxType), DxTypeLoad(rhs.dxType)));
            return *this;
        }

        inline Vector3f RotateVector(const Vector3f& vec) const
        {
            Vector3f result;
            auto xmVector = DirectX::XMVector3Rotate(DirectX::XMLoadFloat3(&vec.dxType), DxTypeLoad(dxType));
            DirectX::XMStoreFloat3(&result.dxType, xmVector);
            return result;
        }

        inline Quaternion GetInverse() const
        {
            Quaternion result;
            DxTypeStore(result.dxType, DirectX::XMQuaternionInverse(DxTypeLoad(dxType)));
            return result;
        }

    private:
        inline static DirectX::XMVECTOR DxTypeLoad(const DirectX::XMFLOAT4& dxt)
        {
            return DirectX::XMLoadFloat4(&dxt);
        }
        inline static void DxTypeStore(DirectX::XMFLOAT4& dxType, DirectX::XMVECTOR xmv)
        {
            DirectX::XMStoreFloat4(&dxType, xmv);
        }
    };

} // namespace ost