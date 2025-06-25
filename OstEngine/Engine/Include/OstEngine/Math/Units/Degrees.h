// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"

// ------------------------------------------------------------

namespace ost
{
	struct Radians;

	struct Degrees
	{
		Degrees();
		Degrees(float32 v);
		Degrees(const Radians& d);
		Degrees(const Degrees& r) = default;

		operator Radians() const;
		float32 Get() const;

		Degrees& operator=(const Degrees&) = default;
		bool operator==(Degrees d);

	private:
		float32 _value;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------