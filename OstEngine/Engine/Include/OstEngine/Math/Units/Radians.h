// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"

// ------------------------------------------------------------

namespace ost
{
	struct Degrees;

	struct Radians
	{
		Radians();
		Radians(float32 v);
		Radians(const Degrees& d);
		Radians(const Radians& r) = default;

		operator Degrees() const;
		float32 Get() const;

		Radians& operator=(const Radians&) = default;
		bool operator==(Radians r);

	private:
		float32 _value;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------