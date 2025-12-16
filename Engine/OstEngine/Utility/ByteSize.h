#pragma once
#include <OstEngine/Types.h>

namespace ByteSize
{
    template <Uint64 TBytesPerUnit>
    struct TByteSize
    {
        constexpr static Uint64 BytesPerUnit = TBytesPerUnit;

        explicit inline TByteSize( Uint64 aUnits )
            : Num{ aUnits }
        {
        }

        explicit inline TByteSize( const TByteSize& aOther )
            : Num{ aOther.Num }
        {
        }

        template <typename TOtherUnit>
        explicit inline TByteSize( const TOtherUnit& aOther )
        {
            const Uint64 bytes = aOther.Num * TOtherUnit::BytesPerUnit;
            Num = bytes / BytesPerUnit;
        }

        TByteSize& operator=( const TByteSize& aOther )
        {
            Num = aOther.Num;
            return *this;
        }

        template <typename TOtherUnit>
        TByteSize& operator=( const TOtherUnit& aOther )
        {
            const Uint64 bytes = aOther.Num * TOtherUnit::BytesPerUnit;
            Num = bytes / BytesPerUnit;
            return *this;
        }

        Uint64 Num;
    };

    using Bytes = TByteSize<1u>;
    using Kilobytes = TByteSize<Bytes::BytesPerUnit * 1024>;
    using Megabytes = TByteSize<Kilobytes::BytesPerUnit * 1024>;
    using Gigabytes = TByteSize<Megabytes::BytesPerUnit * 1024>;
} // namespace ByteSize