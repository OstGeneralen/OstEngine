// OstEngine - Copyright(c) 2025 Kasper Esbj�rnsson (MIT License)
#pragma once
#include "OstEngine/BasicTypes.h"

#include <string>
#include <unordered_map>

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		struct SLogScope;
	}

	struct SCommandArgs;
	struct CConfigFile;

	struct SConfig
	{
	public:
		void ParseCommandLine(const SCommandArgs& args);
		void ParseConfigFile(const CConfigFile& cfg);

	protected:
		void Register(const std::string& config, bool& value);
		void Register(const std::string& config, int32& value);
		void Register(const std::string& config, float32& value);
		void Register(const std::string& config, std::string& value);

	private:
		enum class EValueType { Flag, Integer, Float, String };
		struct SValue { EValueType vT; void* vP; };
		
		void ForeachConfigValue(const std::string& nStr, const std::string& vStr);

		std::unordered_map<std::string, SValue> _registeredValues;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------