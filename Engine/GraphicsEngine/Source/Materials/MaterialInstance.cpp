// Kasper "OstGeneralen" Esbjornsson - 2026
#include "GraphicsEngine/Materials/MaterialInstance.h"

#include "GraphicsEngine/Materials/Material.h"
#include "Resources/GraphicsResourceManager.h"

// RHI
#include "RHI/RHIInternal.h"
#include "RHI/RenderHardwareInterface.h"

using namespace ost;

// ------------------------------------------------------------

MaterialInstance::MaterialInstance(MaterialHandle hRootMaterial, IGraphicsResourceManager& resourceManagerInterface)
{
}

MaterialInstance::MaterialInstance(MaterialInstance&&) noexcept = default;

// ------------------------------------------------------------

MaterialPropertyCollection& ost::MaterialInstance::Properties()
{
    return _propertyCollection;
}

const MaterialPropertyCollection& ost::MaterialInstance::Properties() const
{
    return _propertyCollection;
}

// ------------------------------------------------------------

MaterialHandle ost::MaterialInstance::GetRootMaterialHandle() const
{
    return _materialHandle;
}

BufferHandle ost::MaterialInstance::GetPropertyBufferHandle() const
{
    return _propertyBufferHandle;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------