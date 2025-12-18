#pragma once
#include "OstEngine/Types.h"
#include "OstEngine/Math/Matrix4x4.h"
#include <d3d11.h>

namespace ost
{
	namespace dx
	{
		extern void InitializeEngineDefaults();
        extern ID3D11InputLayout* CreateInputLayout( void* aBufPtr, Uint64 aBufSize );

		extern void UseEngineDefaults();

		extern void UpdatePerObjectBuffer( const TMatrix4x4<float>& aModelMat );

        extern ID3D11Buffer* WorldDataBuffer;
        extern ID3D11Buffer* PerObjectBuffer;
		extern ID3D11SamplerState* SamplerState;
	}
}