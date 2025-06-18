// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

#include "OstEngine/BasicTypes.h"

// ------------------------------------------------------------

namespace ost
{
	class IRenderTarget
	{
	public:
		virtual ~IRenderTarget() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual uint32 GetW() const = 0;
		virtual uint32 GetH() const = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------