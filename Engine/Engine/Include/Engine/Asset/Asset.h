// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include <OstTypes.h>

#include <Utility/TypeID.h>

// ------------------------------------------------------------

namespace ost
{
    class Asset
    {
    public:
        Asset() = default;
        Asset(const Asset&) = delete;
        Asset(Asset&& asset) noexcept;
        virtual ~Asset() = default;

        Asset& operator=(const Asset&) = delete;
        Asset& operator=(Asset&& asset) noexcept;

        void AddReference();
        void ReleaseReference();
        SizeType GetRefCount() const;

        virtual TypeID AssetTypeID() const = 0;

    private:
        SizeType _references = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------