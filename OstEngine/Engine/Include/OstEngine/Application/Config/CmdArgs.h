// OstEngine - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include <string>
#include <vector>
#include <functional>

// ------------------------------------------------------------

namespace ost
{
	enum class ECommandArgType
	{
		Command,
		Value,
	};

	struct SCommandArg
	{
		SCommandArg(const std::string& content)
			: _content(content)
		{
			if (_content[0] == '-')
				_type = ECommandArgType::Command;
			else
				_type = ECommandArgType::Value;
		}

		const std::string& GetString() const { return _content; }
		const ECommandArgType GetType() const { return _type; }
		
	private:
		std::string _content;
		ECommandArgType _type;
	};

	struct SCommandArgs
	{
	public:
		SCommandArgs(char* cstrArgs[], int numArgs);
		SCommandArgs(const char* argStr);
		SCommandArgs(const wchar_t* argStr);

		using ArgsIT_f = std::function<void(const std::string&, const std::string&)>;
		void ForeachCommand(ArgsIT_f itFunc) const;

	private:
		void BuildCommandArgsList(const std::string& fromStr);
		std::vector<SCommandArg> _splitCommandLine;
	};
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------