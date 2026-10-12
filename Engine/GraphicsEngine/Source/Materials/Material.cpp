// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Material.h"

#include "MaterialInstance.h"
#include "RHI/RHIInternal.h"

using namespace ost;

// ------------------------------------------------------------

Material::Material() = default;
Material::Material(Material&&) noexcept = default;
Material::~Material() = default;

// ------------------------------------------------------------

void Material::Create(const BackendMaterialDesc& desc)
{
    List<MaterialProperty> propertyList;
    for (const auto& [propertyName, property] : desc.properties.propertyMap)
    {
        propertyList.Add(property);
    }
    _propertyDefaults = MaterialPropertyCollection(propertyList, desc.properties.totalSize);

    _textureDefaults = MaterialTextureCollection(desc.textureDescs);

    _pso = desc.pso;
}

// ------------------------------------------------------------

void Material::PopulateInstanceProperties(MaterialInstance& instance) const
{
    _propertyDefaults.CopyPropertyData(static_cast<MaterialPropertyCollection&>(instance.Properties()));
    instance.Textures() = _textureDefaults;
}

const SizeType ost::Material::GetPropertiesBufferSize() const
{
    return _propertyDefaults.GetPropertyDataByteSize();
}

const PipelineStateObject& Material::GetPSO() const
{
    return _pso;
}

// ------------------------------------------------------------

IMaterialPropertyCollection& Material::GetPropertyDefaults()
{
    return _propertyDefaults;
}

MaterialTextureCollection& ost::Material::GetTextureDefaults()
{
    return _textureDefaults;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------