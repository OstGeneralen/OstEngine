// Kasper "OstGeneralen" Esbjornsson - 2026
#include "Engine/Graphics/Material/MaterialProperty.h"

using namespace ost;

// ------------------------------------------------------------

ost::MaterialProperty::MaterialProperty(const std::string& name, TypeID typeID, SizeType dataSize, void* pMemory)
    : _name{name}
    , _typeID{typeID}
    , _dataSize{dataSize}
    , _pMemory{pMemory}
{
}

// ------------------------------------------------------------

const std::string& ost::MaterialProperty::GetName() const
{
    return _name;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------