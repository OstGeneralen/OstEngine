// Kasper "OstGeneralen" Esbjornsson - 2026
#pragma once
#include "GraphicsEngine/Rendering/Vertex.h"
#include "Objects/Buffer.h"
#include "Objects/Shader.h"

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

        void InitializeResources( const RenderHardwareInterface& rhi );

        const RenderResourceMesh& GetBlitMesh() const;
        const Shader& GetBlitVertexShader() const;
        const Shader& GetBlitPixelShader() const;

        const ComPtr<RHIBlendState>& GetBlendState(EBlendState blendMode) const;

    private:
        void InitializeBlendStates(const RenderHardwareInterface& rhi);
        void InitializeBlitResources(const RenderHardwareInterface& rhi);

        static RenderResourceLibrary* pInstance;

        ComPtr<RHIBlendState> _blendStates[static_cast<Uint32>(EBlendState::COUNT)];

        RenderResourceMesh _blitMesh;
        Shader _blitVertexShader;
        Shader _blitPixelShader;
    };
} // namespace ost

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------