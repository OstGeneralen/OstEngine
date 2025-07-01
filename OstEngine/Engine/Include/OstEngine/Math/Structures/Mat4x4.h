// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Math/Structures/Vector4.h"
#include "OstEngine/Math/Structures/Mat3x3.h"

// ------------------------------------------------------------

namespace ost
{
	template<FloatingPointType T>
	class TMatrix4x4
	{
	public:
		static TMatrix4x4 CreateTranslation(const TVector3<T>& t)
		{
			TMatrix4x4<T> mat;
			mat.Elements[12] = t.X;
			mat.Elements[13] = t.Y;
			mat.Elements[14] = t.Z;
			return mat;
		}

		static TMatrix4x4 CreateScale(const TVector3<T>& s)
		{
			TMatrix4x4<T> mat;
			mat.Elements[0] = s.X;
			mat.Elements[5] = s.Y;
			mat.Elements[10] = s.Z;
			return mat;
		}

	public:
		T Elements[4 * 4];

		TMatrix4x4();
		TMatrix4x4(const TVector4<T>& r1, const TVector4<T>& r2, const TVector4<T>& r3, const TVector4<T>& r4);
		TMatrix4x4(const TMatrix4x4&) = default;


		TMatrix4x4 GetTransposed() const;
		TMatrix4x4& Transpose();

		TMatrix4x4 operator*(const TMatrix4x4& rhs) const;
		TMatrix4x4& operator*=(const TMatrix4x4& rhs);

		TMatrix4x4 GetFastInverse() const;

	public:
		TMatrix4x4& SetRow1(const TVector4<T>& v);
		TMatrix4x4& SetRow2(const TVector4<T>& v);
		TMatrix4x4& SetRow3(const TVector4<T>& v);
		TMatrix4x4& SetRow4(const TVector4<T>& v);

		TVector4<T> GetRow1() const;
		TVector4<T> GetRow2() const;
		TVector4<T> GetRow3() const;
		TVector4<T> GetRow4() const;

		TMatrix4x4& SetCol1(const TVector4<T>& v);
		TMatrix4x4& SetCol2(const TVector4<T>& v);
		TMatrix4x4& SetCol3(const TVector4<T>& v);
		TMatrix4x4& SetCol4(const TVector4<T>& v);

		TVector4<T> GetCol1() const;
		TVector4<T> GetCol2() const;
		TVector4<T> GetCol3() const;
		TVector4<T> GetCol4() const;
	};

	template<FloatingPointType T>
	static TVector4<T> operator*(const TVector4<T>& v, const TMatrix4x4<T>& m)
	{
		return TVector4{ v.Dot(m.GetCol1()), v.Dot(m.GetCol2()), v.Dot(m.GetCol3()), v.Dot(m.GetCol4()) };
	}

	template<FloatingPointType T>
	static TVector4<T> operator*(const TMatrix4x4<T>& m, const TVector4<T>& v)
	{
		return TVector4{ v.Dot(m.GetRow1()), v.Dot(m.GetRow2()), v.Dot(m.GetRow3()), v.Dot(m.GetRow4()) };
	}
}

// ------------------------------------------------------------
// DEF
// ------------------------------------------------------------
template<ost::FloatingPointType T>
ost::TMatrix4x4<T>::TMatrix4x4()
	: Elements{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1 }
{
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>::TMatrix4x4(const TVector4<T>& r1, const TVector4<T>& r2, const TVector4<T>& r3, const TVector4<T>& r4)
{
	SetRow1(r1);
	SetRow2(r2);
	SetRow3(r3);
	SetRow4(r4);
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::SetRow1(const TVector4<T>& v)
{
	Elements[0] = v.X;
	Elements[4] = v.Y;
	Elements[8] = v.Z;
	Elements[12] = v.W;
	return *this;
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::SetRow2(const TVector4<T>& v)
{
	Elements[1] = v.X;
	Elements[5] = v.Y;
	Elements[9] = v.Z;
	Elements[13] = v.W;
	return *this;
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::SetRow3(const TVector4<T>& v)
{
	Elements[2] = v.X;
	Elements[6] = v.Y;
	Elements[10] = v.Z;
	Elements[14] = v.W;
	return *this;
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::SetRow4(const TVector4<T>& v)
{
	Elements[3] = v.X;
	Elements[7] = v.Y;
	Elements[11] = v.Z;
	Elements[15] = v.W;
	return *this;
}

template<ost::FloatingPointType T>
inline ost::TVector4<T> ost::TMatrix4x4<T>::GetRow1() const
{
	return TVector4<T>{Elements[0], Elements[4], Elements[8], Elements[12]};
}

template<ost::FloatingPointType T>
inline ost::TVector4<T> ost::TMatrix4x4<T>::GetRow2() const
{
	return TVector4<T>{Elements[1], Elements[5], Elements[9], Elements[13]};
}

template<ost::FloatingPointType T>
inline ost::TVector4<T> ost::TMatrix4x4<T>::GetRow3() const
{
	return TVector4<T>{Elements[2], Elements[6], Elements[10], Elements[14]};
}

template<ost::FloatingPointType T>
inline ost::TVector4<T> ost::TMatrix4x4<T>::GetRow4() const
{
	return TVector4<T>{Elements[3], Elements[7], Elements[11], Elements[15]};
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::SetCol1(const TVector4<T>& v)
{
	Elements[0] = v.X;
	Elements[1] = v.Y;
	Elements[2] = v.Z;
	Elements[3] = v.W;
	return *this;
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::SetCol2(const TVector4<T>& v)
{
	Elements[4] = v.X;
	Elements[5] = v.Y;
	Elements[6] = v.Z;
	Elements[7] = v.W;
	return *this;
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::SetCol3(const TVector4<T>& v)
{
	Elements[8] = v.X;
	Elements[9] = v.Y;
	Elements[10] = v.Z;
	Elements[11] = v.W;
	return *this;
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::SetCol4(const TVector4<T>& v)
{
	Elements[12] = v.X;
	Elements[13] = v.Y;
	Elements[14] = v.Z;
	Elements[15] = v.W;
	return *this;
}

template<ost::FloatingPointType T>
inline ost::TVector4<T> ost::TMatrix4x4<T>::GetCol1() const
{
	return TVector4<T>{Elements[0], Elements[1], Elements[2], Elements[3]};
}

template<ost::FloatingPointType T>
inline ost::TVector4<T> ost::TMatrix4x4<T>::GetCol2() const
{
	return TVector4<T>{Elements[4], Elements[5], Elements[6], Elements[7]};
}

template<ost::FloatingPointType T>
inline ost::TVector4<T> ost::TMatrix4x4<T>::GetCol3() const
{
	return TVector4<T>{Elements[8], Elements[9], Elements[10], Elements[11]};
}

template<ost::FloatingPointType T>
inline ost::TVector4<T> ost::TMatrix4x4<T>::GetCol4() const
{
	return TVector4<T>{Elements[12], Elements[13], Elements[14], Elements[15]};
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T> ost::TMatrix4x4<T>::GetTransposed() const
{
	return TMatrix4x4(GetCol1(), GetCol2(), GetCol3(), GetCol4());
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::Transpose()
{
	const TVector4<T> r1 = GetRow1();
	const TVector4<T> r2 = GetRow2();
	const TVector4<T> r3 = GetRow3();
	const TVector4<T> r4 = GetRow4();
	SetCol1(r1);
	SetCol2(r2);
	SetCol3(r3);
	SetCol4(r4);
	return *this;
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T> ost::TMatrix4x4<T>::operator*(const TMatrix4x4& rhs) const
{
	const TVector4<T> MulCol1 = rhs.GetCol1();
	const TVector4<T> MulCol2 = rhs.GetCol2();
	const TVector4<T> MulCol3 = rhs.GetCol3();
	const TVector4<T> MulCol4 = rhs.GetCol4();

	const TVector4<T> ThisRow1 = GetRow1();
	const TVector4<T> ThisRow2 = GetRow2();
	const TVector4<T> ThisRow3 = GetRow3();
	const TVector4<T> ThisRow4 = GetRow4();

	return TMatrix4x4{
		TVector4<T>{ ThisRow1.Dot(MulCol1), ThisRow1.Dot(MulCol2), ThisRow1.Dot(MulCol3), ThisRow1.Dot(MulCol4) },
		TVector4<T>{ ThisRow2.Dot(MulCol1), ThisRow2.Dot(MulCol2), ThisRow2.Dot(MulCol3), ThisRow2.Dot(MulCol4) },
		TVector4<T>{ ThisRow3.Dot(MulCol1), ThisRow3.Dot(MulCol2), ThisRow3.Dot(MulCol3), ThisRow3.Dot(MulCol4) },
		TVector4<T>{ ThisRow4.Dot(MulCol1), ThisRow4.Dot(MulCol2), ThisRow4.Dot(MulCol3), ThisRow4.Dot(MulCol4) }
	};
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T>& ost::TMatrix4x4<T>::operator*=(const TMatrix4x4& rhs)
{
	const TVector4<T> MulCol1 = rhs.GetCol1();
	const TVector4<T> MulCol2 = rhs.GetCol2();
	const TVector4<T> MulCol3 = rhs.GetCol3();
	const TVector4<T> MulCol4 = rhs.GetCol4();

	const TVector4<T> ThisRow1 = GetRow1();
	const TVector4<T> ThisRow2 = GetRow2();
	const TVector4<T> ThisRow3 = GetRow3();
	const TVector4<T> ThisRow4 = GetRow4();

	SetRow1(TVector4<T>{ ThisRow1.Dot(MulCol1), ThisRow1.Dot(MulCol2), ThisRow1.Dot(MulCol3), ThisRow1.Dot(MulCol4) });
	SetRow2(TVector4<T>{ ThisRow2.Dot(MulCol1), ThisRow2.Dot(MulCol2), ThisRow2.Dot(MulCol3), ThisRow2.Dot(MulCol4) });
	SetRow3(TVector4<T>{ ThisRow3.Dot(MulCol1), ThisRow3.Dot(MulCol2), ThisRow3.Dot(MulCol3), ThisRow3.Dot(MulCol4) });
	SetRow4(TVector4<T>{ ThisRow4.Dot(MulCol1), ThisRow4.Dot(MulCol2), ThisRow4.Dot(MulCol3), ThisRow4.Dot(MulCol4) });

	return *this;
}

template<ost::FloatingPointType T>
ost::TMatrix4x4<T> ost::TMatrix4x4<T>::GetFastInverse() const
{
	// Argument vectors describes the ROWS of the 3x3 matrix
	const TMatrix3x3<T> subMatrix{
		{ Elements[0], Elements[4], Elements[8] },
		{ Elements[1], Elements[5], Elements[9] },
		{ Elements[2], Elements[6], Elements[10] }
	};
	const TMatrix3x3<T> invSubMatrix = subMatrix.GetInverse();
	const TVector3<T> transVec = (invSubMatrix * TVector3<T>{ Elements[12], Elements[13], Elements[14] }) * T{ -1 };

	// Again, each vector given here is a ROW of the 4x4 matrix
	return TMatrix4x4{
		TVector4<T>{ invSubMatrix.Elements[0], invSubMatrix.Elements[3], invSubMatrix.Elements[6], transVec.X},
		TVector4<T>{ invSubMatrix.Elements[1], invSubMatrix.Elements[4], invSubMatrix.Elements[7], transVec.Y},
		TVector4<T>{ invSubMatrix.Elements[2], invSubMatrix.Elements[5], invSubMatrix.Elements[8], transVec.Z },
		GetRow4() // Keep row4
	};
}


// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------