#pragma once

namespace ost
{
    template <typename T>
    class TMatrix2x2
    {
    public:
        T M11, M21;
        T M12, M22;

    public:
        TMatrix2x2();
        TMatrix2x2( T a11, T a21, T a12, T a22 );
        TMatrix2x2( const TMatrix2x2& ) = default;

        TMatrix2x2& Transpose();
        TMatrix2x2 GetTransposed() const;

        TMatrix2x2 GetInverse() const;

        T GetDeterminant() const;
    };

    template <typename T>
    inline ost::TMatrix2x2<T>::TMatrix2x2()
        : M11{ 1 }
        , M21{ 0 }
        , M12{ 0 }
        , M22{ 1 }
    {
    }

    template <typename T>
    inline ost::TMatrix2x2<T>::TMatrix2x2( T a11, T a21, T a12, T a22 )
        : M11{ a11 }
        , M21{ a21 }
        , M12{ a12 }
        , M22{ a22 }
    {
    }

    template<typename T>
    inline TMatrix2x2<T>& ost::TMatrix2x2<T>::Transpose()
    {
        std::swap( M21, M12 );
        return *this;
    }
    template <typename T>
    inline TMatrix2x2<T> ost::TMatrix2x2<T>::GetTransposed() const
    {
        TMatrix2x2<T> result = *this;
        return result.Transpose();
    }

    template<typename T>
    inline T ost::TMatrix2x2<T>::GetDeterminant() const
    {
        const T posFactor = M11 * M22;
        const T negFactor = M21 * M12;
        return posFactor - negFactor;
    }
} // namespace ost