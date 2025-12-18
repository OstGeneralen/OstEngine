#pragma once
#include <OstEngine/Rendering/RenderCore.h>
#include <OstEngine/Math/Matrix4x4.h>

namespace ost
{
	CBUFFER_STRUCTURE struct SEngineDataRenderInput
	{
        TMatrix4x4<float> ViewProjectionMatrix;
        CBUFFER_DATA( Float32, TotalTime )
	};
}