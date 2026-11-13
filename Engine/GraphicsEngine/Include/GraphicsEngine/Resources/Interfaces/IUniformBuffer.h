// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Resources/Interfaces/IGraphicsResource.h"

// ------------------------------------------------------------

namespace ost
{
    DECLARE_GFX_RESOURCE_HANDLE(HUniformBuffer);

    struct IUniformBuffer : public IGraphicsResource
    {
        virtual void WriteData(const void* pData, SizeType size) = 0;
        virtual SizeType GetDataSize() const = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------