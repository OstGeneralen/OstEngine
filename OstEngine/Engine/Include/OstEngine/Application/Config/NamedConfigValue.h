// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once

#include <string>

// ------------------------------------------------------------

namespace ost
{
	struct SNamedConfigValue
	{
		SNamedConfigValue() = default;
		SNamedConfigValue(const std::string cmdStr, const std::string valStr = "")
			: _commandName(cmdStr)
			, _commandValue(valStr)
		{
		}
		SNamedConfigValue(const SNamedConfigValue&) = default;
		SNamedConfigValue(SNamedConfigValue&&) noexcept = default;

		SNamedConfigValue& operator=(const SNamedConfigValue&) = default;
		SNamedConfigValue& operator=(SNamedConfigValue&&) noexcept = default;

		bool operator==(const std::string& s) const
		{
			return _commandName == s;
		}

		float ReadAsFloat(float defVal = 0.0f) const
		{
			try { return std::stof(_commandValue); }
			catch (std::exception e) {}
			return defVal;
		}
		
		int ReadAsInt(int defVal = 0) const
		{
			try { return std::stoi(_commandValue); }
			catch (std::exception e) {}
			return defVal;
		}

		std::string ReadAsString() const
		{
			return _commandValue;
		}

		const bool HasValue() const
		{
			return _commandValue.size() > 0;
		}

		const std::string& Name() const { return _commandName; }
		const std::string& Value() const { return _commandValue; }

	private:
		std::string _commandName;
		std::string _commandValue;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------