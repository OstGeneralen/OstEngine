#pragma once
#include <OstEngine/Math/Color.h>
#include <Src/Rendering/DX/DXRenderState.h>
#include <string>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

namespace ost
{
    class CWindow;

    struct SDXRendererDebugInfo
    {
        std::string AdapterName;
        Uint64 VRAM;
    };

	class CDXRenderer
	{
    public:
        const SDXRendererDebugInfo& GetDebugInfo() const;
        CDXRenderState CreateRenderState( const std::string& aRenderStateName );
    };
}