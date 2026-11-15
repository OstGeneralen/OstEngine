// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/GraphicsTypes.h"
#include "GraphicsEngine/Rendering/Vertex.h"
#include "GraphicsEngine/Resources/IGraphicsResource.h"

// ------------------------------------------------------------

namespace ost
{
    DECLARE_GFX_RESOURCE_HANDLE(HUniformBuffer);
    DECLARE_GFX_RESOURCE_HANDLE(HVertexBuffer);
    DECLARE_GFX_RESOURCE_HANDLE(HIndexBuffer);

    // ------------------------------------------------------------

    struct IUniformBuffer : public IGraphicsResource
    {
        virtual SizeType GetDataSize() const = 0;
        virtual void SetData(const void* pData, SizeType size) = 0;
    };

    // ------------------------------------------------------------

    struct IVertexBuffer : public IGraphicsResource
    {
        virtual EVertexType GetVertexType() const = 0;
        virtual SizeType GetVertexSize() const = 0;
        virtual SizeType GetVertexCount() const = 0;
    };

    // ------------------------------------------------------------

    struct IIndexBuffer : public IGraphicsResource
    {
        virtual SizeType GetIndexCount() const = 0;
    };

} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------