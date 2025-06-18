// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstEngine/Subsystem/IAssetsSystem.h"

// ------------------------------------------------------------

namespace ost
{
	class CAssetsSystem : public IAssetsSystem
	{
	public: // CAssetsSystem
		CAssetsSystem();
		void SetRootPath(const std::filesystem::path& rootPath);

	public: // IAssetsSystem
		std::filesystem::path MakeAssetPath(const std::filesystem::path& assetRelPath) const override;

	private:
		std::filesystem::path _assetsRootPath;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------