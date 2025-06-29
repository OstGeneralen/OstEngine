// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"

#include "OstEngine/Math/CommonMath.h"
#include "OstEngine/Math/MathUtils.h"
#include "OstEngine/Math/Matrices/Mat4x4.h"
#include "OstEngine/Math/Vectors/Vector3.h"
#include "OstEngine/Math/Units/Radians.h"

namespace ost
{
	template<FloatingPointType T>
	class TQuaternion
	{
	public:
		static TQuaternion FromEuler(Radians x, Radians y, Radians z)
		{
			const T c_half = static_cast<T>(0.5);
			const T yaw = y.Get();
			const T pitch = x.Get();
			const T roll = z.Get();

			const T cy = math::Cos(yaw * c_half);
			const T sy = math::Sin(yaw * c_half);
			const T cp = math::Cos(pitch * c_half);
			const T sp = math::Sin(pitch * c_half);
			const T cr = math::Cos(roll * c_half);
			const T sr = math::Sin(roll * c_half);

			return TQuaternion{
				sr * cp * cy - cr * sp * sy,
				cr * sp * cy + sr * cp * sy,
				cr * cp * sy - sr * sp * cy,
				cr * cp * cy + sr * sp * sy
			};
		}

		static TQuaternion FromAxisAngle(const TVector3<T>& axis, Radians angle)
		{
			const T halfAngle = angle.Get() * static_cast<T>(0.5);
			const T s = math::Sin(halfAngle);
			return TQuaternion{
				axis.X * s,
				axis.Y * s,
				axis.Z * s,
				math::Cos(halfAngle)
			};
		}

	public:
		T X, Y, Z, W;

		constexpr TQuaternion();
		constexpr TQuaternion(T x, T y, T z, T w);
		TQuaternion(const TQuaternion& q) = default;

		TQuaternion Inverse() const;

		void Normalize();
		T Magnitude() const;
		T MagnitudeSqr() const;

		T Dot(const TQuaternion& q) const;
		TQuaternion operator*(const TQuaternion& q) const;
		TVector3<T> operator*(const TVector3<T>& v) const;
		TQuaternion& operator*=(const TQuaternion& q);
		TQuaternion& operator=(const TQuaternion&) = default;

		TMatrix4x4<T> ToRotationMatrix() const;
	};

	template<FloatingPointType T>
	constexpr TQuaternion<T>::TQuaternion()
		: X{0}, Y{0}, Z{0}, W{1}
	{
	}

	template<FloatingPointType T>
	constexpr TQuaternion<T>::TQuaternion(T x, T y, T z, T w)
		: X{x}, Y{y}, Z{z}, W{w}
	{
	}

	template<FloatingPointType T>
	TQuaternion<T> ost::TQuaternion<T>::Inverse() const
	{
		return TQuaternion{ -X, -Y, -Z, W };
	}

	template<FloatingPointType T>
	void TQuaternion<T>::Normalize()
	{
		const T magnitude = Magnitude();
		if (magnitude > 0)
		{
			const T invMag = static_cast<T>(1.0) / magnitude;
			X *= invMag;
			Y *= invMag;
			Z *= invMag;
			W *= invMag;
		}
	}

	template<FloatingPointType T>
	T TQuaternion<T>::Magnitude() const
	{
		return math::Sqrt(MagnitudeSqr());
	}

	template<FloatingPointType T>
	T TQuaternion<T>::MagnitudeSqr() const
	{
		return (X * X) + (Y * Y) + (Z * Z) + (W * W);
	}

	template<FloatingPointType T>
	T TQuaternion<T>::Dot(const TQuaternion& q) const
	{
		return (X * q.X) + (Y * q.Y) + (Z * q.Z) + (W * q.W);
	}

	template<FloatingPointType T>
	inline TVector3<T> ost::TQuaternion<T>::operator*(const TVector3<T>& v) const
	{
		TVector3<T> quatVec{ X, Y, Z };
		TVector3<T> uv = quatVec.Cross(v);
		TVector3<T> uuv = quatVec.Cross(uv);
		uv *= (static_cast<T>(2) * W);
		uuv *= static_cast<T>(2);
		return v + uv + uuv;
	}

	template<FloatingPointType T>
	inline TQuaternion<T> TQuaternion<T>::operator*(const TQuaternion& q) const
	{
		return TQuaternion{
			W * q.X + X * q.W + Y * q.Z - Z * q.Y,
			W * q.Y - X * q.Z + Y * q.W + Z * q.X,
			W * q.Z + X * q.Y - Y * q.X + Z * q.W,
			W * q.W - X * q.X - Y * q.Y - Z * q.Z
		};
	}

	template<FloatingPointType T>
	TQuaternion<T>& TQuaternion<T>::operator*=(const TQuaternion<T>& q)
	{
		const T oX = X;
		const T oY = Y;
		const T oZ = Z;
		const T oW = W;

		X = oW * q.X + oX * q.W + oY * q.Z - oZ * q.Y;
		Y = oW * q.Y - oX * q.Z + oY * q.W + oZ * q.X;
		Z = oW * q.Z + oX * q.Y - oY * q.X + oZ * q.W;
		W = oW * q.W - oX * q.X - oY * q.Y - oZ * q.Z;

		return *this;
	}

	template<FloatingPointType T>
	TMatrix4x4<T> TQuaternion<T>::ToRotationMatrix() const
	{
		TMatrix4x4<T> res{};
		
		const T x2 = X + X;
		const T y2 = Y + Y;
		const T z2 = Z + Z;

		const T xx2 = X * x2;
		const T xy2 = X * y2;
		const T xz2 = X * z2;
		const T yy2 = Y * y2;
		const T yz2 = Y * z2;
		const T zz2 = Z * z2;
		const T wx2 = W * x2;
		const T wy2 = W * y2;
		const T wz2 = W * z2;

		res.Elements[0] = static_cast<T>(1) - (yy2 + zz2);
		res.Elements[1] = xy2 + wz2;
		res.Elements[2] = xz2 - wy2;

		res.Elements[4] = xy2 - wz2;
		res.Elements[5] = static_cast<T>(1) - (xx2 + zz2);
		res.Elements[6] = yz2 + wx2;

		res.Elements[8] = xz2 + wy2;
		res.Elements[9] = yz2 - wx2;
		res.Elements[10] = static_cast<T>(1) - (xx2 + yy2);

		return res;
	}


	using Quaternion = TQuaternion<float32>;
}
