#pragma once
#include <OstEngine/OstEngineMinimal.h>
#include <OstEngine/Rendering/DX/DXModel.h>
#include <string>

namespace ost
{
	namespace ModelLoading
	{
        extern void Load( const std::string& aPath, CDXModel& aInto );
	}
}