// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#include "OstEngine/Utility/PathUtils.h"

// ------------------------------------------------------------

std::string ost::path_utils::GetNormalizedPathString(const std::filesystem::path& path)
{
	std::string pathStr = path.string();
	std::replace(pathStr.begin(), pathStr.end(), '\\', '/');
	return std::move(pathStr);
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------