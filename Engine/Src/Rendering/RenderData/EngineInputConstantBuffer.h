#pragma once
#include <OstEngine/Rendering/RenderCore.h>
#include <OstEngine/Common/Math/Matrix4x4.h>

namespace ost
{
	CBUFFER_STRUCTURE struct SEngineDataRenderInput
	{
        Matrix4x4 ViewProjectionMatrix;
        CBUFFER_DATA( Float32, TotalTime )
	};
}