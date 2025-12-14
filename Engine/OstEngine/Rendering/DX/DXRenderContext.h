// ------------------------------------------------------------
// OstEngine/Rendering/DX/DXRenderContext.h
// ------------------------------------------------------------
// Static/onepoint accessors to the commonly used interfaces
// of D3D11 to simplify resource creation.
// 
// These values are initialized by the DXRenderer on its
// initialization.
// ------------------------------------------------------------

#pragma once

#include <d3d11.h>
#include <dxgi.h>

namespace ost
{
	namespace dx
	{
        extern ID3D11Device* Device;
        extern ID3D11DeviceContext* DeviceContext;
	}
}