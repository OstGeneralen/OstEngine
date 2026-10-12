// Kasper "OstGeneralen" Esbjornsson - 2026
#include "MaterialPropertyCollection.h"

using namespace ost;

// ------------------------------------------------------------

MaterialPropertyCollection::MaterialPropertyCollection(const List<MaterialProperty>& properties, SizeType totalSize)
{

    _data = List<Uint8>(totalSize);

    for (const MaterialProperty& descProp : properties)
    {
        const SizeType dataEnd = descProp.dataByteOffset + MaterialPropertyType::GetByteSize(descProp.type);

        const SizeType propertyIndex = _properties.GetSize();
        _properties.Add(descProp);
        _propertyNameToIndex.Insert(descProp.name, propertyIndex);
    }
}

// ------------------------------------------------------------

void MaterialPropertyCollection::CopyPropertyData(MaterialPropertyCollection& into) const
{
    into._data = List<Uint8>(_data.GetSize());
    MemCopy(into._data.GetData(), _data.GetData(), _data.GetSize());

    into._propertyNameToIndex = _propertyNameToIndex;
    into._properties = _properties;
}

// ------------------------------------------------------------

const Uint8* MaterialPropertyCollection::GetPropertyData() const
{
    return _data.GetData();
}

SizeType MaterialPropertyCollection::GetPropertyDataByteSize() const
{
    return _data.GetSize();
}

// ------------------------------------------------------------

bool MaterialPropertyCollection::TryGetPropertyIndex(const std::string& name, SizeType& outIndex) const
{
    if (const SizeType* i = _propertyNameToIndex.TryGetValue(name))
    {
        outIndex = *i;
        return true;
    }
    return false;
}

EMaterialPropertyType MaterialPropertyCollection::GetPropertyType(SizeType index) const
{
    return _properties[index].type;
}

// ------------------------------------------------------------

void MaterialPropertyCollection::SetProperty(SizeType index, const void* data, SizeType dataSize)
{
    MemCopy(_data.GetData() + _properties[index].dataByteOffset, data, dataSize);
}

const void* MaterialPropertyCollection::GetProperty(SizeType index) const
{
    return (_data.GetData() + _properties[index].dataByteOffset);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------