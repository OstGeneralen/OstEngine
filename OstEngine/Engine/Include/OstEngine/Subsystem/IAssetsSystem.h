// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <filesystem>

// ------------------------------------------------------------

namespace ost
{
	class IAssetsSystem
	{
	public:
		virtual std::filesystem::path MakeAssetPath(const std::filesystem::path& assetRelPath) const = 0;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------