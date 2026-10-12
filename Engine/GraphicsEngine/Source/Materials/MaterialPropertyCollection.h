// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Materials/IMaterialPropertyCollection.h"
#include "GraphicsEngine/Materials/MaterialPropertyTypes.h"

#include <string>

#include <Container/List.h>
#include <Container/Map.h>
#include <Memory/Memory.h>

// ------------------------------------------------------------

namespace ost
{
    struct MaterialProperty
    {
        std::string name;
        EMaterialPropertyType type;
        SizeType dataByteOffset;
    };

    class MaterialPropertyCollection : public IMaterialPropertyCollection
    {
    public:
        MaterialPropertyCollection() = default;
        MaterialPropertyCollection(const List<MaterialProperty>& properties, SizeType totalSize);
        MaterialPropertyCollection(const MaterialPropertyCollection&) = delete;
        MaterialPropertyCollection(MaterialPropertyCollection&&) noexcept = default;

        MaterialPropertyCollection& operator=(const MaterialPropertyCollection&) = delete;
        MaterialPropertyCollection& operator=(MaterialPropertyCollection&&) noexcept = default;

        void CopyPropertyData(MaterialPropertyCollection& into) const;

        const Uint8* GetPropertyData() const;
        SizeType GetPropertyDataByteSize() const;

        // BEGIN IMaterialPropertyCollection
        bool TryGetPropertyIndex(const std::string& name, SizeType& outIndex) const override;
        EMaterialPropertyType GetPropertyType(SizeType index) const override;

        void SetProperty(SizeType index, const void* data, SizeType dataSize) override;
        const void* GetProperty(SizeType index) const override;
        // END IMaterialPropertyCollection

    private:
        List<MaterialProperty> _properties;
        Map<std::string, SizeType> _propertyNameToIndex;
        List<Uint8> _data;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------