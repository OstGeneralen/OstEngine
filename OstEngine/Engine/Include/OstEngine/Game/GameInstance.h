// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
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