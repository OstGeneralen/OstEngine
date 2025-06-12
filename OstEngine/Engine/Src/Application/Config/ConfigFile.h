// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <filesystem>
#include <vector>
#include <functional>

// ------------------------------------------------------------

namespace ost
{
	class CConfigFile
	{
	public:
		CConfigFile(const std::filesystem::path& path);

		void ForeachConfigValue(std::function<void(const std::string&, const std::string&)> itF) const;

	private:
		void Parse(const std::string& line);

		struct NameValuePair
		{
			std::string Name;
			std::string ValueStr;
		};
		std::vector<NameValuePair> _nvPairs;
	};

}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------