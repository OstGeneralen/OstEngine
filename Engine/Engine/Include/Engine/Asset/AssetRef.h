// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once

// ------------------------------------------------------------

namespace ost
{
    class Asset;

    struct AssetRefBase
    {
    public:
        AssetRefBase();
        AssetRefBase(Asset* pAsset);
        AssetRefBase(const AssetRefBase&);
        AssetRefBase(AssetRefBase&&) noexcept;
        virtual ~AssetRefBase();

        AssetRefBase& operator=(const AssetRefBase&);
        AssetRefBase& operator=(AssetRefBase&&) noexcept;
        AssetRefBase& operator=(std::nullptr_t);

        operator bool() const;

    protected:
        Asset* Get();
        const Asset* Get() const;

    private:
        Asset* _pAsset;
    };

    // ------------------------------------------------------------

    template <typename T>
    struct AssetRef : public AssetRefBase
    {
        AssetRef() = default;
        AssetRef(T* pAsset)
            : AssetRefBase{pAsset}
        {
        }
        AssetRef(const AssetRef&) = default;
        AssetRef(AssetRef&&) noexcept = default;
        ~AssetRef() = default;

        AssetRef& operator=(const AssetRef&) = default;
        AssetRef& operator=(AssetRef&&) noexcept = default;
        AssetRef& operator=(std::nullptr_t)
        {
            AssetRefBase::operator=(nullptr);
            return *this;
        }

        T* operator->()
        {
            return static_cast<T*>(Get());
        }
        const T* operator->() const
        {
            return static_cast<const T*>(Get());
        }

        T& operator*()
        {
            return *static_cast<T*>(Get());
        }
        const T& operator*() const
        {
            return *static_cast<const T*>(Get());
        }

        operator bool() const
        {
            return AssetRefBase::operator bool();
        }
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------