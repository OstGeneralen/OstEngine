// Kasper "OstGeneralen" Esbjornsson - 2026
#include "MaterialInstance.h"

#include "RHI/RHIInternal.h"

using namespace ost;

// ------------------------------------------------------------

MaterialInstance::MaterialInstance() = default;
MaterialInstance::MaterialInstance(MaterialInstance&&) noexcept = default;
MaterialInstance::~MaterialInstance() = default;

// ------------------------------------------------------------

void MaterialInstance::Create(const MaterialInstanceDesc& desc)
{
    _propertiesBuffer = desc.propertyBuffer;
    _baseMaterialHandle = desc.baseMaterialHandle;
}

// ------------------------------------------------------------

HMaterial MaterialInstance::GetBaseMaterialHandle() const
{
    return _baseMaterialHandle;
}

const Buffer& MaterialInstance::GetPropertiesBuffer() const
{
    return _propertiesBuffer;
}

const Uint8* MaterialInstance::GetPropertiesData() const
{
    return _properties.GetPropertyData();
}

SizeType MaterialInstance::GetPropertiesDataSize() const
{
    return _properties.GetPropertyDataByteSize();
}

// ------------------------------------------------------------

IMaterialPropertyCollection& MaterialInstance::Properties()
{
    return _properties;
}

const IMaterialPropertyCollection& MaterialInstance::Properties() const
{
    return _properties;
}

MaterialTextureCollection& ost::MaterialInstance::Textures()
{
    return _textures;
}

const MaterialTextureCollection& ost::MaterialInstance::Textures() const
{
    return _textures;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------