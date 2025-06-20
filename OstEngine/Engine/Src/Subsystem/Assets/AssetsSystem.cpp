// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "Subsystem/Assets/AssetsSystem.h"
#include "OstEngine/Utility/PathUtils.h"

#include <OstLog/OstLogger.h>

OSTLOG_LOG_INSTANCE(AssetsSystemLog);

// ------------------------------------------------------------

ost::CAssetsSystem::CAssetsSystem()
{
}

// ------------------------------------------------------------

void ost::CAssetsSystem::SetRootPath(const std::filesystem::path& rootPath)
{
	if (std::filesystem::exists(rootPath) == false)
	{
		AssetsSystemLog.LogScoped(OstLogLevel::Warning, "The provided root path does not exist, no assets will be found");
		AssetsSystemLog.Log(OstLogLevel::Warning,  "{}", path_utils::GetNormalizedPathString(rootPath));
		AssetsSystemLog.EndScope();
		_assetsRootPath.clear();
		return;
	}

	_assetsRootPath = rootPath;
}

// ------------------------------------------------------------

std::filesystem::path ost::CAssetsSystem::MakeAssetPath(const std::filesystem::path& assetRelPath) const
{
	return _assetsRootPath / assetRelPath;
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------