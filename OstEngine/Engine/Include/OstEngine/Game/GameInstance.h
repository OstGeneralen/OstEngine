// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <string>

// ------------------------------------------------------------

namespace ost
{
	class IGameInstance
	{
	public:
		virtual ~IGameInstance() = default;
		virtual std::string GameTitle() const = 0;
		virtual void Run() = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------