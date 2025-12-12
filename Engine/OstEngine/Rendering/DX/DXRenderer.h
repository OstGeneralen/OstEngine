#pragma once
#include <OstEngine/Math/Color.h>

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11RenderTargetView;

namespace ost
{
    class CWindow;

	class CDXRenderer
	{
    public:
        void Initialize( CWindow& aWindow );
        void Deinitialize();

        void Clear( const SColor& aClearColor );
        void Present();

	private:
        IDXGISwapChain* _swapChainPtr;
        ID3D11Device* _devicePtr;
        ID3D11DeviceContext* _deviceContextPtr;
        ID3D11RenderTargetView* _renderTargetViewPtr;
    };
}