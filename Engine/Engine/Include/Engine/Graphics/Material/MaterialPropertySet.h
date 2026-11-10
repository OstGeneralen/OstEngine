// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "Engine/Graphics/Material/MaterialProperty.h"

#include <string>

#include <Container/List.h>
#include <Container/Map.h>

// ------------------------------------------------------------

namespace ost
{
    struct MaterialPropertyDesc
    {
        TypeID type;
        std::string name;
        SizeType byteSize;
    };

    class MaterialPropertySet
    {
    public:
        MaterialPropertySet(const List<MaterialPropertyDesc>& propertyDescs);

        MaterialProperty& operator[](SizeType idx);
        const MaterialProperty& operator[](SizeType idx) const;

        MaterialProperty& operator[](const std::string& name);
        const MaterialProperty& operator[](const std::string& name) const;

        SizeType GetPropertyIndex(const std::string& name) const;
        const std::string& GetPropertyName(SizeType idx) const;

        const List<Uint8>& GetBytes() const;
    private:
        Map<std::string, Uint64> _propertyNameToIndex;
        List<MaterialProperty> _properties;
        List<Uint8> _memory;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------