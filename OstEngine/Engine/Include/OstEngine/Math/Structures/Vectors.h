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

	// ------------------------------------------------------------
	// Convert
	// ------------------------------------------------------------
	namespace vec_cast_internal
	{
		template<typename T>
		static inline TVector3<T> V4_to_V3(const TVector4<T>& v) { return TVector3<T>{v.X, v.Y, v.Z}; }

		template<typename T>
		static inline TVector2<T> V4_to_V2(const TVector4<T>& v) { return TVector2<T>{v.X, v.Y}; }

		template<typename T>
		static inline TVector2<T> V3_to_V2(const TVector3<T>& v) { return TVector2<T>{v.X, v.Y}; }
	}

	template<typename To, typename From> 
	static To Vector_Cast(const From& v) { static_assert(false); }

	template<> static inline Vector3f Vector_Cast<Vector3f, Vector4f>(const Vector4f& v) { return vec_cast_internal::V4_to_V3<float32>(v); }
	template<> static inline Vector2f Vector_Cast<Vector2f, Vector4f>(const Vector4f& v) { return vec_cast_internal::V4_to_V2<float32>(v); }
	template<> static inline Vector2f Vector_Cast<Vector2f, Vector3f>(const Vector3f& v) { return vec_cast_internal::V3_to_V2<float32>(v); }

	template<> static inline Vector3d Vector_Cast<Vector3d, Vector4d>(const Vector4d& v) { return vec_cast_internal::V4_to_V3<float64>(v); }
	template<> static inline Vector2d Vector_Cast<Vector2d, Vector4d>(const Vector4d& v) { return vec_cast_internal::V4_to_V2<float64>(v); }
	template<> static inline Vector2d Vector_Cast<Vector2d, Vector3d>(const Vector3d& v) { return vec_cast_internal::V3_to_V2<float64>(v); }
	
	template<> static inline Vector3i Vector_Cast<Vector3i, Vector4i>(const Vector4i& v) { return vec_cast_internal::V4_to_V3<int32>(v); }
	template<> static inline Vector2i Vector_Cast<Vector2i, Vector4i>(const Vector4i& v) { return vec_cast_internal::V4_to_V2<int32>(v); }
	template<> static inline Vector2i Vector_Cast<Vector2i, Vector3i>(const Vector3i& v) { return vec_cast_internal::V3_to_V2<int32>(v); }
	
	template<> static inline Vector3u Vector_Cast<Vector3u, Vector4u>(const Vector4u& v) { return vec_cast_internal::V4_to_V3<uint32>(v); }
	template<> static inline Vector2u Vector_Cast<Vector2u, Vector4u>(const Vector4u& v) { return vec_cast_internal::V4_to_V2<uint32>(v); }
	template<> static inline Vector2u Vector_Cast<Vector2u, Vector3u>(const Vector3u& v) { return vec_cast_internal::V3_to_V2<uint32>(v); }
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------