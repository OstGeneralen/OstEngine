// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/MaterialPropertyTypes.h"

#include <string>

// ------------------------------------------------------------

namespace ost
{

    class IMaterialPropertyCollection
    {
    public:
        ~IMaterialPropertyCollection() = default;

        template <typename T>
        bool SetProperty(const std::string& name, const T& value)
        {
            SizeType propertyIndex;
            if (TryGetPropertyIndex(name, propertyIndex))
            {
                SetProperty(propertyIndex, value);
            }
            return false;
        }

        template <typename T>
        bool SetProperty(SizeType index, const T& value)
        {
            if (MaterialPropertyType::MatchType<T>(GetPropertyType(index)))
            {
                SetProperty(index, &value, sizeof(T));
                return true;
            }
            return false;
        }

        template <typename T>
        const T* GetProperty(const std::string& name) const
        {
            SizeType propertyIndex;
            if (TryGetPropertyIndex(name, propertyIndex))
            {
                return GetProperty(propertyIndex);
            }
            return nullptr;
        }

        template <typename T>
        const T* GetProperty(SizeType index) const
        {
            if (MaterialPropertyType::MatchType<T>(GetPropertyType(index)))
            {
                return reinterpret_cast<const T*>(GetProperty(index));
            }
            return nullptr;
        }

    public:
        virtual bool TryGetPropertyIndex(const std::string& name, SizeType& outIndex) const = 0;
        virtual EMaterialPropertyType GetPropertyType(SizeType index) const = 0;

    protected:
        virtual void SetProperty(SizeType index, const void* data, SizeType dataSize) = 0;
        virtual const void* GetProperty(SizeType index) const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------