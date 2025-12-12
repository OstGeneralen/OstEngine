#pragma once
#include <OstEngine/Math/Color.h>
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
        void Initialize( CWindow& aWindow );
        void Deinitialize();

        void Clear( const SColor& aClearColor );
        void Present();

        ID3D11Device* GetDevicePointer();
        ID3D11DeviceContext* GetDeviceContextPointer();
        const SDXRendererDebugInfo& GetDebugInfo() const;

	private:
        SDXRendererDebugInfo _debugInfo;

        IDXGISwapChain* _swapChainPtr;
        ID3D11Device* _devicePtr;
        ID3D11DeviceContext* _deviceContextPtr;
        ID3D11RenderTargetView* _renderTargetViewPtr;
    };
}