#pragma once
#include <OstEngine/OstEngineMinimal.h>

#include <string>

#include <d3d11.h>
#include <dxgi.h>

namespace ost
{
    struct SDXInputElementDesc
    {
        SDXInputElementDesc();

        std::string SemanticName;
        D3D11_INPUT_ELEMENT_DESC D3DDesc;
    };

    struct SDXRenderStateDescriptor
    {
        constexpr static Uint8 MaxElemDescsCount = 16u;

        void InitFromFile( const std::string& aPath );

        std::string PixelMain;
        std::string VertexMain;

        Uint32 NumElements;
        SDXInputElementDesc ElementDescs[MaxElemDescsCount];

        bool IsValid() const;

    private:
        bool _valid;
    };
} // namespace ost