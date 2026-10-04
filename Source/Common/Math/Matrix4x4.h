// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#pragma once
#include "Math/Math.h"
#include "Math/Matrix3x3.h"
#include "Math/Vector4.h"

#include <OstTypes.h>

#include <DirectXMath/DirectXMath.h>

// ------------------------------------------------------------

namespace ost
{
    class Matrix4x4
    {
    public:
        // clang-format off
        union
        {
            DirectX::XMFLOAT4X4 dxType;
            struct 
            { 
                Float32 m11, m12, m13, m14;
                Float32 m21, m22, m23, m24;
                Float32 m31, m32, m33, m34;
                Float32 m41, m42, m43, m44;
            };
            Float32 m[4][4];
        };
        // clang-format on

    public:
        inline static Matrix4x4 CreateTransformMatrix(const Vector3f& translation, const Quaternion& rotation, const Vector3f& scale)
        {
            Matrix4x4 result;
            StoreDxType(result.dxType, DirectX::XMMatrixAffineTransformation(DirectX::XMLoadFloat3(&scale.dxType), DirectX::XMVectorZero(),
                                                                             DirectX::XMLoadFloat4(&rotation.dxType), DirectX::XMLoadFloat3(&translation.dxType)));
            return result;
        }

        inline static Matrix4x4 CreateTransformMatrix(const Vector3f& translation, const Quaternion& rotation)
        {
            Matrix4x4 result;
            const DirectX::XMFLOAT3 scale = {1, 1, 1};
            StoreDxType(result.dxType, DirectX::XMMatrixAffineTransformation(DirectX::XMLoadFloat3(&scale), DirectX::XMVectorZero(),
                                                                             DirectX::XMLoadFloat4(&rotation.dxType), DirectX::XMLoadFloat3(&translation.dxType)));
            return result;
        }

        inline static Matrix4x4 CreatePerspectiveProjection(Float32 fovYRad, Float32 aspect, Float32 nearZ, Float32 farZ)
        {
            Matrix4x4 result;
            StoreDxType(result.dxType, DirectX::XMMatrixPerspectiveFovLH(fovYRad, aspect, nearZ, farZ));
            return result;
        }

        inline static Matrix4x4 CreateOrthographicsProjection(Float32 sizeX, Float32 sizeY, Float32 nearZ, Float32 farZ)
        {
            Matrix4x4 result;
            StoreDxType(result.dxType, DirectX::XMMatrixOrthographicLH(sizeX, sizeY, nearZ, farZ));
            return result;
        }

    public:
        // clang-format off
        Matrix4x4()
            : m11{1}, m12{0}, m13{0}, m14{0}
            , m21{0}, m22{1}, m23{0}, m24{0}
            , m31{0}, m32{0}, m33{1}, m34{0}
            , m41{0}, m42{0}, m43{0}, m44{1}
        {
        }

        Matrix4x4(const Matrix3x3& rhs)
            : m11{rhs.m11}, m12{rhs.m12}, m13{rhs.m13}, m14{0}
            , m21{rhs.m21}, m22{rhs.m22}, m23{rhs.m23}, m24{0}
            , m31{rhs.m31}, m32{rhs.m32}, m33{rhs.m33}, m34{0}
            , m41{0}, m42{0}, m43{0}, m44{1}
        {
        }

        Matrix4x4(const Matrix4x4& rhs)
            : dxType{rhs.dxType}
        {
        }

        Matrix4x4(  Float32 v11, Float32 v12, Float32 v13, Float32 v14,
                    Float32 v21, Float32 v22, Float32 v23, Float32 v24, 
                    Float32 v31, Float32 v32, Float32 v33, Float32 v34, 
                    Float32 v41, Float32 v42, Float32 v43, Float32 v44 )
            : m11{v11}, m12{v12}, m13{v13}, m14{v14}
            , m21{v21}, m22{v22}, m23{v23}, m24{v24}
            , m31{v31}, m32{v32}, m33{v33}, m34{v34}
            , m41{v41}, m42{v42}, m43{v43}, m44{v34}
        {
        }

        // clang-format on

        inline Matrix4x4 operator*(const Matrix4x4& rhs) const
        {
            Matrix4x4 result;
            StoreDxType(result.dxType, DirectX::XMMatrixMultiply(LoadDxType(dxType), LoadDxType(rhs.dxType)));
            return result;
        }
        inline Matrix4x4& operator*=(const Matrix4x4& rhs)
        {
            StoreDxType(dxType, DirectX::XMMatrixMultiply(LoadDxType(dxType), LoadDxType(rhs.dxType)));
            return *this;
        }

        inline Matrix4x4 GetInverse() const
        {
            auto xmMat = LoadDxType(dxType);
            DirectX::XMVECTOR determinant = DirectX::XMMatrixDeterminant(xmMat);

            Matrix4x4 inverted;
            StoreDxType(inverted.dxType, DirectX::XMMatrixInverse(&determinant, xmMat));
            return inverted;
        }

        inline operator Matrix3x3() const
        {
            return Matrix3x3{m11, m12, m13, m21, m22, m23, m31, m32, m33};
        }

    private:
        static inline DirectX::XMMATRIX LoadDxType(const DirectX::XMFLOAT4X4& dxt)
        {
            return DirectX::XMLoadFloat4x4(&dxt);
        }
        static inline void StoreDxType(DirectX::XMFLOAT4X4& dxt, DirectX::XMMATRIX dxm)
        {
            return DirectX::XMStoreFloat4x4(&dxt, dxm);
        }
    };

    // External type operators
    static inline Vector4f operator*(const Vector4f& v, const Matrix4x4& m)
    {
        Vector4f result;
        DirectX::XMStoreFloat4(&result.dxType, DirectX::XMVector4Transform(DirectX::XMLoadFloat4(&v.dxType), DirectX::XMLoadFloat4x4(&m.dxType)));
        return result;
    }

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------