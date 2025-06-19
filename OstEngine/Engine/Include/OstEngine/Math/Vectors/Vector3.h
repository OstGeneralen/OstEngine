// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Math/MathUtils.h"
#include "OstEngine/Math/CommonMath.h"

#include "OstEngine/Math/Vectors/Vector2.h"

// ------------------------------------------------------------

namespace ost
{
	template<NumericType T>
	class TVector3
	{
	public:
		T X, Y, Z;

	public:
		TVector3() : TVector3(0, 0, 0) { }
		TVector3(const TVector2<T>& v, T z) : TVector3{ v.X, v.Y, z } {}
		TVector3(const TVector3& v) = default;
		TVector3(T x, T y, T z)
			: X{x}, Y{y}, Z{z}
		{
		}

		TVector3& operator=(const TVector2& v)
		{
			X = v.X;
			Y = v.Y;
			return *this;
		}
		TVector3& operator=(const TVector3&) = default;
		
		bool operator==(const TVector3& r) const
		{
			return NumericEquality::AreEqual<T>(X, r.X) 
				&& NumericEquality::AreEqual<T>(Y, r.Y)
				&& NumericEquality::AreEqual<T>(Z, r.Z);
		}

		TVector3 operator+(const TVector3& r) const
		{
			return TVector3(X + r.X, Y + r.Y, Z + r.Z);
		}

		TVector3 operator-(const TVector3& r) const
		{
			return TVector3(X - r.X, Y - r.Y, Z - r.Z);
		}

		TVector3 operator*(T s) const
		{
			return TVector3(X * s, Y * s, Z * s);
		}

		TVector3 operator / (T s) const
		{
			return TVector3(X / s, Y / s, Z / s);
		}

		TVector3& operator+=(const TVector3& r)
		{
			X += r.X;
			Y += r.Y;
			Z += r.Z;
			return *this;
		}

		TVector3& operator-=(const TVector3& r)
		{
			X -= r.X;
			Y -= r.Y;
			Z -= r.Z;
			return *this;
		}

		TVector3& operator*=(T s)
		{
			X *= s;
			Y *= s;
			Z *= s;
			return *this;
		}

		TVector3& operator/=(T s)
		{
			X /= s;
			Y /= s;
			Z /= s;
			return *this;
		}

		T MagnitudeSqr() const
		{
			return (X * X) + (Y * Y) + (Z * Z);
		}

		T Magnitude() const
		{
			return math::Sqrt(MagnitudeSqr());
		}

		TVector3 GetNormalized() const
		{
			return (*this) / Magnitude();
		}

		TVector3& Normalize()
		{
			return (*this) /= Magnitude();
		}

		T Dot(const TVector3& r) const
		{
			return (X * r.X) + (Y * r.Y) + (Z * r.Z);
		}

		TVector3 Cross(const TVector3& r) const
		{
			return TVector3{
				(Y * r.Z) - (Z * r.Y),
				(Z * r.X) - (X * r.Z),
				(X * r.Y) - (Y * r.X)
			};
		}

		operator TVector2<T>() const
		{
			return TVector2<T>{X, Y};
		}
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------