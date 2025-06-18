// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <filesystem>
#include <string>

namespace ost
{
	namespace path_utils
	{
		extern std::string GetNormalizedPathString(const std::filesystem::path& path);
	}
}