// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"
#include "OstEngine/Math/Structures/Vector2.h"
#include "OstEngine/Math/Structures/Vector3.h"
#include "OstEngine/Math/Structures/Vector4.h"

// ------------------------------------------------------------

namespace ost
{
	// ------------------------------------------------------------
	// Float
	// ------------------------------------------------------------
	using Vector2f = TVector2<float32>;
	using Vector3f = TVector3<float32>;
	using Vector4f = TVector4<float32>;

	// ------------------------------------------------------------
	// Double
	// ------------------------------------------------------------
	using Vector2d = TVector2<float64>;
	using Vector3d = TVector3<float64>;
	using Vector4d = TVector4<float64>;
	
	// ------------------------------------------------------------
	// Signed integer
	// ------------------------------------------------------------
	using Vector2i = TVector2<int32>;
	using Vector3i = TVector3<int32>;
	using Vector4i = TVector4<int32>;

	// ------------------------------------------------------------
	// Unsigned integer
	// ------------------------------------------------------------
	using Vector2u = TVector2<uint32>;
	using Vector3u = TVector3<uint32>;
	using Vector4u = TVector4<uint32>;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------