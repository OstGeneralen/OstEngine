// OstEngine - Copyright(c) 2025 Kasper Esbj�rnsson (MIT License)
#pragma once

// ------------------------------------------------------------

namespace ost
{
	class IGameInstance
	{
	public:
		virtual ~IGameInstance() = default;
		virtual void Run() = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------