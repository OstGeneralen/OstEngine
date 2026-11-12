// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Vertex.h"
#include "Objects/Buffer.h"
#include "Objects/Shader.h"
#include "Objects/StateObjects.h"

// ------------------------------------------------------------

namespace ost
{
    class RenderHardwareInterface;

    struct RenderResourceMesh
    {
        EVertexType vertexType;
        Buffer vertexBuffer;
        Buffer indexBuffer;
        SizeType indexCount;
    };

    class RenderResourceLibrary
    {
    public:
        static const RenderResourceLibrary& Get();

        RenderResourceLibrary();
        ~RenderResourceLibrary();

        void InitializeResources(const RenderHardwareInterface& rhi);

        const RenderResourceMesh& GetBlitMesh() const;
        const Shader& GetBlitVertexShader() const;
        const Shader& GetBlitPixelShader() const;

        const BlendState& GetBlendState(EBlendMode blendMode) const;
        const DepthStencilState& GetDepthStencilState(EDepthMode depthMode) const;

    private:
        void InitializeStateObjects(const RenderHardwareInterface& rhi);
        void InitializeBlitResources(const RenderHardwareInterface& rhi);

        static RenderResourceLibrary* pInstance;

        BlendState _blendStates[static_cast<Uint32>(EBlendMode::COUNT)];
        DepthStencilState _dsStates[static_cast<Uint32>(EDepthMode::COUNT)];

        RenderResourceMesh _blitMesh;
        Shader _blitVertexShader;
        Shader _blitPixelShader;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------