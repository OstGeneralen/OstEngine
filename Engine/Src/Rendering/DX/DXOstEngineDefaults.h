#pragma once
#include <d3d11.h>

namespace ost
{
	namespace dx
	{
		extern void InitializeEngineDefaults();

        extern ID3D11Buffer* WorldDataBuffer;
        extern ID3D11Buffer* PerObjectBuffer;
		extern ID3D11SamplerState* SamplerState;
	}
}