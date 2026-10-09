// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/MaterialPropertyTypes.h"

#include <OstTypes.h>

#include <Container/List.h>
#include <Container/Map.h>
#include <Memory/Memory.h>

// ------------------------------------------------------------

namespace ost
{
    struct MaterialPropertyData
    {
        std::string name;
        EMaterialPropertyType type;
        SizeType byteOffset;
    };

    struct MaterialPropertiesDesc
    {
        List<MaterialPropertyData> properties;
        SizeType totalBytes;
    };

    class MaterialPropertyCollection
    {
    public:
        MaterialPropertyCollection();
        MaterialPropertyCollection(const MaterialPropertiesDesc& desc);
        MaterialPropertyCollection(const MaterialPropertyCollection& other);
        MaterialPropertiesDesc& operator=(const MaterialPropertyCollection& rhs);

        SizeType GetPropertyIndex(const std::string& propertyName) const;
        const std::string& GetPropertyName(SizeType propertyIndex) const;

        const SizeType GetByteSize() const;
        const Uint8* GetData() const;

        template <typename T>
        bool SetPropertyValue(const std::string& propertyName, const T& value)
        {
            if (const SizeType* found = _propertyNameToIndex.TryGetValue(propertyName))
            {
                return SetPropertyValue(*found, value);
            }
            return false;
        }

        template <typename T>
        bool SetPropertyValue(SizeType propertyIndex, const T& value)
        {
            const MaterialPropertyData& propertyData = _properties[propertyIndex].type;

            if (MaterialPropertyType::TypeMatch<T>(propertyData.type))
            {
                MemCopy(_propertyData.GetData() + propertyData.byteOffset, &value, sizeof(T));
                return true;
            }
            return false;
        }

        template <typename T>
        const T* GetPropertyValue(SizeType propertyIndex) const
        {
            const MaterialPropertyData& propertyData = _properties[propertyIndex];
            if (MaterialPropertyType::TypeMatch<T>(propertyData.type))
            {
                return reinterpret_cast<const T*>(_propertyData.GetData() + propertyData.byteOffset);
            }
            return nullptr;
        }

        template <typename T>
        const T* GetPropertyValue(const std::string& propertyName) const
        {
            if (const SizeType* pIndex = _propertyNameToIndex.TryGetValue(propertyName))
            {
                return GetPropertyValue<T>(*pIndex);
            }
            return nullptr;
        }

    private:
        Map<std::string, SizeType> _propertyNameToIndex;
        List<MaterialPropertyData> _properties;
        List<Uint8> _propertyData;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------