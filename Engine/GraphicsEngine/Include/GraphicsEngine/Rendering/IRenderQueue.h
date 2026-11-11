// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Lights.h"
#include "GraphicsEngine/Resources/ObjectHandles.h"

#include <Math/Color.h>
#include <Math/Matrix4x4.h>
#include <Math/Vector3.h>
#include <Memory/Memory.h>
#include <Utility/Hash.h>

// ------------------------------------------------------------

namespace ost
{
    struct RenderView
    {
        Matrix4x4 viewProjection;
        Matrix4x4 viewInverse;
    };

    struct DrawCommand
    {
        Uint64 ShaderHash() const
        {
            Uint64 arr[2] = { vertexShader.AsInteger(), pixelShader.AsInteger() };
            return hash::fnv1a<2>(arr);
        }

        HShader vertexShader;
        HShader pixelShader;
        
        HVertexBuffer vertexBuffer;
        HIndexBuffer indexBuffer;

        Matrix4x4 transform;
    };

    class IRenderQueue
    {
    public:
        virtual ~IRenderQueue() = default;

        virtual void SetView(const Matrix4x4& viewProjection, const Matrix4x4& viewInverse) = 0;
        virtual void AddLight(const LightData& lightData) = 0;
        virtual void Push( const DrawCommand& cmd ) = 0;
        virtual void Finalise() = 0;

        virtual void Clear() = 0;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------