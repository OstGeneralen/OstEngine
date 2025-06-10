// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Utility/EnumFlag.h"

// ------------------------------------------------------------

namespace ost
{
	enum class ELogLevel : uint8
	{
		None		= 0x00,
		Verbose		= 0x01 << 0,
		Log			= 0x01 << 1,
		Info		= 0x01 << 2,
		Confirm		= 0x01 << 3,
		Warning		= 0x01 << 4,
		Error		= 0x01 << 5,
		All			= 0xFF
	};
}
MAKE_ENUM_FLAG(ost::ELogLevel);


// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------