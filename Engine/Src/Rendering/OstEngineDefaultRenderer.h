#pragma once

#include "OstEngine/Math/Matrix4x4.h"
#include "OstEngine/Rendering/RenderData/Vertex.h"
#include "Src/Rendering/RenderData/EngineInputConstantBuffer.h"

#include <d3d11.h>
#include <vector>

namespace ost
{
    struct SDefaultRendererDrawCommand
    {
        SDefaltVertex Vertices[4];
        Matrix4x4 ModelMatrix;
        ID3D11ShaderResourceView* TextureResource;
    };

    class CDefaultRenderer
    {
    public:
        void Initialize();

        void UpdateEngineInput( const SEngineDataRenderInput& aUpdatedData );

        void PerformRender();

    private:
        std::vector<SDefaultRendererDrawCommand> _pendingDraws;

        ID3D11VertexShader* _vertexShader;
        ID3D11PixelShader* _pixelShader;
        ID3D11InputLayout* _inputLayout;
        ID3D11Buffer* _engineInputBuffer;
        ID3D11Buffer* _quadVertexBuffer;
        ID3D11Buffer* _perObjectBuffer;
        ID3D11SamplerState* _samplerState;
    };
} // namespace ost