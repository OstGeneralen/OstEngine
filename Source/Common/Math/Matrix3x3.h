// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#pragma once
#include "Math/Math.h"
#include "Math/Quaternion.h"
#include "Math/Vector4.h"

#include <OstTypes.h>

#include <DirectXMath.h>

// ------------------------------------------------------------

namespace ost
{
    class Matrix3x3
    {
    public:
        // clang-format off
        union
        {
            DirectX::XMFLOAT3X3 dxType;
            struct 
            { 
                Float32 m11, m12, m13;
                Float32 m21, m22, m23;
                Float32 m31, m32, m33;
            };
            Float32 m[3][3];
        };
        // clang-format on

    public:
        static inline Matrix3x3 RotationAroundX(Float32 rad)
        {
            return RotationAroundAxis({1, 0, 0}, rad);
        }

        static inline Matrix3x3 RotationAroundY(Float32 rad)
        {
            return RotationAroundAxis({0, 1, 0}, rad);
        }

        static inline Matrix3x3 RotationAroundZ(Float32 rad)
        {
            return RotationAroundAxis({0, 0, 1}, rad);
        }

        static inline Matrix3x3 RotationAroundAxis(const Vector3f& axis, Float32 rad)
        {
            Matrix3x3 result;
            StoreDxType(result.dxType, DirectX::XMMatrixRotationAxis(DirectX::XMLoadFloat3(&(axis.dxType)), rad));
            return result;
        }

        static inline Matrix3x3 RotationFromQuaternion(const Quaternion& q)
        {
            Matrix3x3 result;
            StoreDxType(result.dxType, DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&q.dxType)));
            return result;
        }

    public:
        // clang-format off
        Matrix3x3()
            : m11{1}, m12{0}, m13{0}
            , m21{0}, m22{1}, m23{0}
            , m31{0}, m32{0}, m33{1}
        {
        }
        Matrix3x3(const Matrix3x3& rhs)
            : dxType{rhs.dxType}
        {
        }
        Matrix3x3(  Float32 v11, Float32 v12, Float32 v13,
                    Float32 v21, Float32 v22, Float32 v23,
                    Float32 v31, Float32 v32, Float32 v33)
            : m11{v11}, m12{v12}, m13{v13}
            , m21{v21}, m22{v22}, m23{v23}
            , m31{v31}, m32{v32}, m33{v33}
        {
        }
        // clang-format on

        inline Matrix3x3 operator*(const Matrix3x3& rhs) const
        {
            Matrix3x3 result;
            StoreDxType(result.dxType, DirectX::XMMatrixMultiply(LoadDxType(dxType), LoadDxType(rhs.dxType)));
            return result;
        }
        inline Matrix3x3& operator*=(const Matrix3x3& rhs)
        {
            StoreDxType(dxType, DirectX::XMMatrixMultiply(LoadDxType(dxType), LoadDxType(rhs.dxType)));
            return *this;
        }

        inline Matrix3x3 GetInverse() const
        {
            auto xmMat = LoadDxType(dxType);
            DirectX::XMVECTOR determinant = DirectX::XMMatrixDeterminant(xmMat);

            Matrix3x3 inverted;
            StoreDxType(inverted.dxType, DirectX::XMMatrixInverse(&determinant, xmMat));
            return inverted;
        }

    private:
        static inline DirectX::XMMATRIX LoadDxType(const DirectX::XMFLOAT3X3& dxt)
        {
            return DirectX::XMLoadFloat3x3(&dxt);
        }
        static inline void StoreDxType(DirectX::XMFLOAT3X3& dxt, DirectX::XMMATRIX dxm)
        {
            return DirectX::XMStoreFloat3x3(&dxt, dxm);
        }
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------