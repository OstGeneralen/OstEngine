// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Graphics/Material/MaterialPropertySet.h"

using namespace ost;

// ------------------------------------------------------------

ost::MaterialPropertySet::MaterialPropertySet(const List<MaterialPropertyDesc>& propertyDescs)
{
    // Pre-calculate the total byte size and allocate the byte memory
    SizeType totalSize = 0;
    for (const auto& desc : propertyDescs)
    {
        totalSize += desc.byteSize;
    }
    _memory = List<Uint8>(totalSize);

    // Build the set of properties
    SizeType memoryOffset = 0;

    for (SizeType i = 0; i < propertyDescs.GetSize(); ++i)
    {
        const auto& desc = propertyDescs[i];

        _propertyNameToIndex.Insert(propertyDescs[i].name, i);
        _properties.Emplace(desc.name, desc.type, desc.byteSize, _memory.GetData() + memoryOffset);
        memoryOffset += propertyDescs[i].byteSize;
    }
}

// ------------------------------------------------------------

MaterialProperty& ost::MaterialPropertySet::operator[](SizeType idx)
{
    return _properties[idx];
}

const MaterialProperty& ost::MaterialPropertySet::operator[](SizeType idx) const
{
    return _properties[idx];
}

MaterialProperty& ost::MaterialPropertySet::operator[](const std::string& name)
{
    return _properties[GetPropertyIndex(name)];
}

const MaterialProperty& ost::MaterialPropertySet::operator[](const std::string& name) const
{
    return _properties[GetPropertyIndex(name)];
}

// ------------------------------------------------------------

SizeType ost::MaterialPropertySet::GetPropertyIndex(const std::string& name) const
{
    return _propertyNameToIndex[name];
}

const std::string& ost::MaterialPropertySet::GetPropertyName(SizeType idx) const
{
    return _properties[idx].GetName();
}

// ------------------------------------------------------------

const List<Uint8>& ost::MaterialPropertySet::GetBytes() const
{
    return _memory;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------