// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Material.h"

#include <d3d11_1.h>

#include <Memory/Memory.h>

using namespace ost;

// ------------------------------------------------------------

Material::Material() = default;
Material::Material(const Material&) = default;
Material::Material(Material&&) noexcept = default;
Material::~Material() = default;

Material& Material::operator=(const Material&) = default;
Material& Material::operator=(Material&&) noexcept = default;

// ------------------------------------------------------------

void Material::SetProperty(const std::string& propertyName, const Texture& t)
{
    if (Property* pProp = _propertyMap.TryGetValue(propertyName))
    {
        if (pProp->type == Property::EType::Texture)
        {
            _pTextureProperties[pProp->offset] = &t;
        }
    }
}

void Material::SetProperty(const std::string& propertyName, const Color& c)
{
    SetVariableProperty(propertyName, &c, sizeof(Color));
}

void Material::SetProperty(const std::string& propertyName, const Vector4f& v)
{
    SetVariableProperty(propertyName, &v, sizeof(Vector4f));
}

void Material::SetProperty(const std::string& propertyName, const Vector3f& v)
{
    SetVariableProperty(propertyName, &v, sizeof(Vector3f));
}

void Material::SetProperty(const std::string& propertyName, const Vector2f& v)
{
    SetVariableProperty(propertyName, &v, sizeof(Vector2f));
}

void Material::SetProperty(const std::string& propertyName, Float32 v)
{
    SetVariableProperty(propertyName, &v, sizeof(Float32));
}

// ------------------------------------------------------------

SizeType Material::GetVariablesByteCount() const
{
    return _variablesByteCount;
}

const void* Material::GetVariablesData() const
{
    return _variablePropertyData;
}

const Buffer& Material::GetVariablesBuffer() const
{
    return _variablesBuffer;
}

// ------------------------------------------------------------

SizeType Material::GetTextureCount() const
{
    return _numTextures;
}

const Texture* Material::GetTextures() const
{
    return _pTextureProperties[0];
}

// ------------------------------------------------------------

const PipelineStateObject& Material::GetPSO() const
{
    return _pso;
}

// ------------------------------------------------------------

void Material::SetVariableProperty(const std::string& propertyName, const void* pData, SizeType dataSize)
{
    if (Property* pProp = _propertyMap.TryGetValue(propertyName))
    {
        if (pProp->type == Property::EType::Variable && pProp->size == dataSize)
        {
            MemCopy(_variablePropertyData + pProp->offset, pData, dataSize);
        }
    }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------