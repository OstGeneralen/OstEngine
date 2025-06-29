// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Math/Structures/Vector3.h"
#include "OstEngine/Math/MathUtils.h"

// ------------------------------------------------------------

namespace ost
{
	template<FloatingPointType T>
	class TMatrix3x3
	{
	public:
		T Elements[3 * 3];

		TMatrix3x3();
		TMatrix3x3(const TMatrix3x3&) = default;
		TMatrix3x3(const TVector3<T>& r1, const TVector3<T>& r2, const TVector3<T>& r3);

		TMatrix3x3 GetTransposed() const;
		TMatrix3x3& Transpose();

		TMatrix3x3 operator*(const TMatrix3x3& rhs) const;
		TMatrix3x3& operator*=(const TMatrix3x3& rhs);

		TMatrix3x3& Invert();
		TMatrix3x3 GetInverse() const;

		T Determinant() const;

	public:
		TVector3<T> GetRow1() const;
		TVector3<T> GetRow2() const;
		TVector3<T> GetRow3() const;

		TMatrix3x3<T>& SetRow1(const TVector3<T>& v);
		TMatrix3x3<T>& SetRow2(const TVector3<T>& v);
		TMatrix3x3<T>& SetRow3(const TVector3<T>& v);

		TVector3<T> GetCol1() const;
		TVector3<T> GetCol2() const;
		TVector3<T> GetCol3() const;

		TMatrix3x3<T>& SetCol1(const TVector3<T>& v);
		TMatrix3x3<T>& SetCol2(const TVector3<T>& v);
		TMatrix3x3<T>& SetCol3(const TVector3<T>& v);

	private:
		TMatrix3x3<T> GetAdjugateMatrix() const;
	};

	template<FloatingPointType T>
	static TVector3<T> operator*(const TVector3<T>& v, const TMatrix3x3<T>& m)
	{
		return TVector3{ v.Dot(m.GetCol1()), v.Dot(m.GetCol2()), v.Dot(m.GetCol3()) };
	}

	template<FloatingPointType T>
	static TVector3<T> operator*(const TMatrix3x3<T>& m, const TVector3<T>& v)
	{
		return TVector3{ v.Dot(m.GetRow1()), v.Dot(m.GetRow2()), v.Dot(m.GetRow3()) };
	}

}

// ------------------------------------------------------------
// DEF
// ------------------------------------------------------------
namespace ost
{
	template<FloatingPointType T>
	TMatrix3x3<T>::TMatrix3x3()
		: Elements{
			1,0,0,
			0,1,0,
			0,0,1}
	{
	}

	template<FloatingPointType T>
	TMatrix3x3<T>::TMatrix3x3(const TVector3<T>& r1, const TVector3<T>& r2, const TVector3<T>& r3)
	{
		SetRow1(r1);
		SetRow2(r2);
		SetRow3(r3);
	}

	template<FloatingPointType T>
	TMatrix3x3<T> TMatrix3x3<T>::GetTransposed() const
	{
		return TMatrix3x3{ GetCol1(), GetCol2(), GetCol3() };
	}

	template<FloatingPointType T>
	TMatrix3x3<T>& TMatrix3x3<T>::Transpose()
	{
		const TVector3<T> r1 = GetRow1();
		const TVector3<T> r2 = GetRow2();
		const TVector3<T> r3 = GetRow3();
		SetCol1(r1);
		SetCol2(r2);
		SetCol3(r3);
		return *this;
	}

	template<FloatingPointType T>
	TMatrix3x3<T> TMatrix3x3<T>::operator*(const TMatrix3x3& rhs) const
	{
		const TVector3<T> mulCol1 = rhs.GetCol1();
		const TVector3<T> mulCol2 = rhs.GetCol2();
		const TVector3<T> mulCol3 = rhs.GetCol3();

		const TVector3<T> thisRow1 = GetRow1();
		const TVector3<T> thisRow2 = GetRow2();
		const TVector3<T> thisRow3 = GetRow3();

		return TMatrix3x3{
			TVector3<T>{ thisRow1.Dot(mulCol1), thisRow1.Dot(mulCol2), thisRow1.Dot(mulCol3) },
			TVector3<T>{ thisRow2.Dot(mulCol1), thisRow2.Dot(mulCol2), thisRow2.Dot(mulCol3) },
			TVector3<T>{ thisRow3.Dot(mulCol1), thisRow3.Dot(mulCol2), thisRow3.Dot(mulCol3) }
		};
	}

	template<FloatingPointType T>
	TMatrix3x3<T>& TMatrix3x3<T>::operator*=(const TMatrix3x3& rhs)
	{
		const TVector3<T> mulCol1 = rhs.GetCol1();
		const TVector3<T> mulCol2 = rhs.GetCol2();
		const TVector3<T> mulCol3 = rhs.GetCol3();

		const TVector3<T> thisRow1 = GetRow1();
		const TVector3<T> thisRow2 = GetRow2();
		const TVector3<T> thisRow3 = GetRow3();

		SetRow1(TVector3<T>{ thisRow1.Dot(mulCol1), thisRow1.Dot(mulCol2), thisRow1.Dot(mulCol3) });
		SetRow2(TVector3<T>{ thisRow2.Dot(mulCol1), thisRow2.Dot(mulCol2), thisRow2.Dot(mulCol3) });
		SetRow3(TVector3<T>{ thisRow3.Dot(mulCol1), thisRow3.Dot(mulCol2), thisRow3.Dot(mulCol3)});
	
		return *this;
	}

	template<FloatingPointType T>
	TMatrix3x3<T> ost::TMatrix3x3<T>::GetInverse() const
	{
		const T det = Determinant();
		// num_util::AreEqual ensures floating point numbers are compared with a small tolerance (accounting for floating point imprecisions)
		if (num_util::AreEqual(det, 0.0f)) 
		{
			return TMatrix3x3<T>(); // Identity
		}

		const T mul = T{ 1 } / det;

		TMatrix3x3<T> mat = GetAdjugateMatrix();
		for (int32 eIdx = 0; eIdx < 9; ++eIdx)
		{
			mat.Elements[eIdx] *= mul;
		}
		return mat;
	}

	template<FloatingPointType T>
	TMatrix3x3<T>& ost::TMatrix3x3<T>::Invert()
	{
		return (*this) = GetInverse();
	}

	template<FloatingPointType T>
	T TMatrix3x3<T>::Determinant() const
	{
		// Determinant defined as a(ei - fh) - d(bi - ch) + g(bf - ce)
		// Where matrix is
		// | a, b, c |
		// | d, e, f |
		// | g, h, i |

		const T cf_a = Elements[0] * ((Elements[4] * Elements[8]) - (Elements[5] * Elements[7]));
		const T cf_b = Elements[1] * ((Elements[3] * Elements[8]) - (Elements[5] * Elements[6]));
		const T cf_c = Elements[2] * ((Elements[3] * Elements[7]) - (Elements[4] * Elements[6]));
		return cf_a - cf_b + cf_c;
	}

	template<FloatingPointType T>
	TVector3<T> TMatrix3x3<T>::GetRow1() const
	{
		return TVector3<T>{ Elements[0], Elements[3], Elements[6] };
	}

	template<FloatingPointType T>
	TVector3<T> TMatrix3x3<T>::GetRow2() const
	{
		return TVector3<T>{ Elements[1], Elements[4], Elements[7] };
	}

	template<FloatingPointType T>
	TVector3<T> TMatrix3x3<T>::GetRow3() const
	{
		return TVector3<T>{ Elements[2], Elements[5], Elements[8] };
	}

	template<FloatingPointType T>
	TMatrix3x3<T>& TMatrix3x3<T>::SetRow1(const TVector3<T>& v)
	{
		Elements[0] = v.X;
		Elements[3] = v.Y;
		Elements[6] = v.Z;
		return *this;
	}

	template<FloatingPointType T>
	TMatrix3x3<T>& TMatrix3x3<T>::SetRow2(const TVector3<T>& v)
	{
		Elements[1] = v.X;
		Elements[4] = v.Y;
		Elements[7] = v.Z;
		return *this;
	}

	template<FloatingPointType T>
	TMatrix3x3<T>& TMatrix3x3<T>::SetRow3(const TVector3<T>& v)
	{
		Elements[2] = v.X;
		Elements[5] = v.Y;
		Elements[8] = v.Z;
		return *this;
	}

	template<FloatingPointType T>
	TVector3<T> TMatrix3x3<T>::GetCol1() const
	{
		return TVector3<T>{ Elements[0], Elements[1], Elements[2] };
	}

	template<FloatingPointType T>
	TVector3<T> TMatrix3x3<T>::GetCol2() const
	{
		return TVector3<T>{ Elements[3], Elements[4], Elements[5] };
	}

	template<FloatingPointType T>
	TVector3<T> TMatrix3x3<T>::GetCol3() const
	{
		return TVector3<T>{ Elements[6], Elements[7], Elements[8] };
	}

	template<FloatingPointType T>
	TMatrix3x3<T>& TMatrix3x3<T>::SetCol1(const TVector3<T>& v)
	{
		Elements[0] = v.X;
		Elements[1] = v.Y;
		Elements[2] = v.Z;
		return *this;
	}

	template<FloatingPointType T>
	TMatrix3x3<T>& TMatrix3x3<T>::SetCol2(const TVector3<T>& v)
	{
		Elements[3] = v.X;
		Elements[4] = v.Y;
		Elements[5] = v.Z;
		return *this;
	}

	template<FloatingPointType T>
	TMatrix3x3<T>& TMatrix3x3<T>::SetCol3(const TVector3<T>& v)
	{
		Elements[6] = v.X;
		Elements[7] = v.Y;
		Elements[8] = v.Z;
		return *this;
	}

	template<FloatingPointType T>
	TMatrix3x3<T> TMatrix3x3<T>::GetAdjugateMatrix() const
	{
		// Adjugate matrix
		// +(48 - 57) -(18 - 27) +(15 - 24)
		// -(38 - 56) +(08 - 26) -(05 - 23)
		// +(37 - 46) -(07 - 16) +(04 - 13)
		// For the matrix
		// a0 b1 c2
		// d3 e4 f5
		// g6 h7 i8

		const TVector3<T> r1{
			+((Elements[4] * Elements[8]) - (Elements[5] * Elements[7])),
			-((Elements[1] * Elements[8]) - (Elements[2] * Elements[7])),
			+((Elements[1] * Elements[5]) - (Elements[2] * Elements[4]))
		};

		const TVector3<T> r2{
			-((Elements[3] * Elements[8]) - (Elements[5] * Elements[6])),
			+((Elements[0] * Elements[8]) - (Elements[2] * Elements[6])),
			-((Elements[0] * Elements[5]) - (Elements[2] * Elements[3]))
		};

		const TVector3<T> r3{
			+((Elements[3] * Elements[7]) - (Elements[4] * Elements[6])),
			-((Elements[0] * Elements[7]) - (Elements[1] * Elements[6])),
			+((Elements[0] * Elements[4]) - (Elements[1] * Elements[3]))
		};

		return TMatrix3x3{ r1, r2,r3 };
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------