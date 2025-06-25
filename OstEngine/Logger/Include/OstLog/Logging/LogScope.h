// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/APIDefinition.h"
#include "OstLog/Logging/LogLevel.h"
#include "OstLog/Logging/LogMessage.h"

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class CLogInstance;

		struct LOGGER_API SLogScope
		{
			friend CLogInstance;

		public:
			SLogScope(SLogScope&& o) noexcept;
			SLogScope(const SLogScope&) = delete;
			~SLogScope();

			template<typename ... TFmt>
			void Log(std::format_string<TFmt...> fmtStr, TFmt&&... fmtArgs)
			{
				SLogMessage msg;
				msg.Level = _rootMessage.Level;
				msg.LoggerName = _rootMessage.LoggerName;
				msg.Timestamp = _rootMessage.Timestamp;
				msg.Source = _rootMessage.Source;
				msg.MessageFormatter = [fmtStr, ...args = std::forward<TFmt>(fmtArgs)]() mutable {
					return std::format(fmtStr, std::forward<TFmt>(args)...);
					};
				_rootMessage.SubMessages.push_back(msg);
			}

		private:
			SLogScope(SLogMessage rootMessage);
			SLogMessage _rootMessage;
			bool _isValid;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------