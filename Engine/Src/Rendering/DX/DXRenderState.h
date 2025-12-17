#pragma once
#include <Src/Rendering/DX/DXConstantBuffer.h>

struct ID3D11VertexShader;
struct ID3D11PixelShader;
struct ID3D11InputLayout;

namespace ost
{
    class CDXRenderer;

    class CDXRenderState
    {
        friend CDXRenderer;

    public:
        CDXRenderState();
        CDXRenderState( CDXRenderState&& aOther ) noexcept;
        CDXRenderState( const CDXRenderState& ) = delete;
        ~CDXRenderState();

        CDXRenderState& operator=( const CDXRenderState& ) = delete;
        CDXRenderState& operator=( CDXRenderState&& aOther ) noexcept;

        void Bind();
        void BindConstantBuffer(const CDXConstantBuffer& aBuffer);

        void Unbind();



    private:
        CDXRenderState( CDXRenderer& aParentRenderer, ID3D11VertexShader* aVS, ID3D11PixelShader* aPS,
                           ID3D11InputLayout* aIL );

        CDXRenderer* _renderer;
        ID3D11VertexShader* _vertexShader;
        ID3D11PixelShader* _pixelShader;
        ID3D11InputLayout* _inputLayout;
    };
} // namespace ost