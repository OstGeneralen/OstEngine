// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Math/MathUtils.h"
#include "OstEngine/Math/CommonMath.h"

// ------------------------------------------------------------

namespace ost
{
	template<NumericType T>
	class TVector2
	{
	public:
		T X, Y;

	public:
		TVector2() : TVector2(0, 0) {}
		TVector2(const TVector2& v) = default;
		TVector2(T x, T y)
			: X{ x }, Y{ y }
		{
		}

		TVector2& operator=(const TVector2&) = default;

		bool operator==(const TVector2& r) const
		{
			return num_util::AreEqual<T>(X, r.X)
				&& num_util::AreEqual<T>(Y, r.Y);
		}

		TVector2 operator+(const TVector2& r) const
		{
			return TVector2(X + r.X, Y + r.Y);
		}

		TVector2 operator-(const TVector2& r) const
		{
			return TVector2(X - r.X, Y - r.Y);
		}

		TVector2 operator*(T s) const
		{
			return TVector2(X * s, Y * s);
		}

		TVector2 operator / (T s) const
		{
			return TVector2(X / s, Y / s);
		}

		TVector2& operator+=(const TVector2& r)
		{
			X += r.X;
			Y += r.Y;
			return *this;
		}

		TVector2& operator-=(const TVector2& r)
		{
			X -= r.X;
			Y -= r.Y;
			return *this;
		}

		TVector2& operator*=(T s)
		{
			X *= s;
			Y *= s;
			return *this;
		}

		TVector2& operator/=(T s)
		{
			X /= s;
			Y /= s;
			return *this;
		}

		T MagnitudeSqr() const
		{
			return (X * X) + (Y * Y);
		}

		T Magnitude() const
		{
			return math::Sqrt(MagnitudeSqr());
		}

		TVector2 GetNormalized() const
		{
			return (*this) / Magnitude();
		}

		TVector2& Normalize()
		{
			return (*this) /= Magnitude();
		}

		T Dot(const TVector2& r) const
		{
			return (X * r.X) + (Y * r.Y);
		}
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
