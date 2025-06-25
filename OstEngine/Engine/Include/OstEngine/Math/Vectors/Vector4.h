// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Math/MathUtils.h"
#include "OstEngine/Math/CommonMath.h"

#include "OstEngine/Math/Vectors/Vector3.h"

// ------------------------------------------------------------

namespace ost
{
	template<NumericType T>
	class TVector4
	{
	public:
		T X, Y, Z, W;

	public:
		TVector4() : TVector4(0, 0, 0, 0) {}
		TVector4(const TVector3<T>& v) : TVector4{ v, 1 } {}
		TVector4(const TVector3<T>& v, T w) : TVector4{ v.X, v.Y, v.Z, w } {}
		TVector4(const TVector4& v) = default;
		TVector4(T x, T y, T z, T w)
			: X{ x }, Y{ y }, Z{ z }, W{w}
		{
		}

		TVector4& operator=(const TVector3<T>& v, T w)
		{
			X = v.X;
			Y = v.Y;
			Z = v.Z;
			W = w;
			return *this;
		}
		TVector4& operator=(const TVector3<T>& v)
		{
			X = v.X;
			Y = v.Y;
			Z = v.Z;
			W = 1;
			return *this;
		}
		TVector4& operator=(const TVector4&) = default;

		bool operator==(const TVector4& r) const
		{
			return NumericEquality::AreEqual<T>(X, r.X)
				&& NumericEquality::AreEqual<T>(Y, r.Y)
				&& NumericEquality::AreEqual<T>(Z, r.Z)
				&& NumericEquality::AreEqual<T>(W, r.W);
		}

		TVector4 operator+(const TVector4& r) const
		{
			return TVector4(X + r.X, Y + r.Y, Z + r.Z, W + r.W);
		}

		TVector4 operator-(const TVector4& r) const
		{
			return TVector4(X - r.X, Y - r.Y, Z - r.Z, W - r.W);
		}

		TVector4 operator*(T s) const
		{
			return TVector4(X * s, Y * s, Z * s, W * s);
		}

		TVector4 operator / (T s) const
		{
			return TVector4(X / s, Y / s, Z / s, W / s);
		}

		TVector4& operator+=(const TVector4& r)
		{
			X += r.X;
			Y += r.Y;
			Z += r.Z;
			W += r.W;
			return *this;
		}

		TVector4& operator-=(const TVector4& r)
		{
			X -= r.X;
			Y -= r.Y;
			Z -= r.Z;
			W -= r.W;
			return *this;
		}

		TVector4& operator*=(T s)
		{
			X *= s;
			Y *= s;
			Z *= s;
			W *= s;
			return *this;
		}

		TVector4& operator/=(T s)
		{
			X /= s;
			Y /= s;
			Z /= s;
			W /= s;
			return *this;
		}

		T MagnitudeSqr() const
		{
			return (X * X) + (Y * Y) + (Z * Z) + (W * W);
		}

		T Magnitude() const
		{
			return math::Sqrt(MagnitudeSqr());
		}

		TVector4 GetNormalized() const
		{
			return (*this) / Magnitude();
		}

		TVector4& Normalize()
		{
			return (*this) /= Magnitude();
		}

		T Dot(const TVector4& r) const
		{
			return (X * r.X) + (Y * r.Y) + (Z * r.Z) + (W * r.W);
		}

		operator TVector3<T>() const
		{
			return TVector3{ X,Y,Z };
		}
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------