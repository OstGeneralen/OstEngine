// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/LogMessage.h"

// ------------------------------------------------------------

namespace ost
{
	namespace log
	{
		class ILogger
		{
		public: // LOG FUNCTIONS
			template<typename ... TFmt>
			void TRACE(std::format_string<TFmt...> str, TFmt&&... args) { Log(ELogLevel::Trace, str, std::forward<TFmt>(args)...); }

			template<typename ... TFmt>
			void DEBUG(std::format_string<TFmt...> str, TFmt&&... args) { Log(ELogLevel::Debug, str, std::forward<TFmt>(args)...); }

			template<typename ... TFmt>
			void INFO(std::format_string<TFmt...> str, TFmt&&... args) { Log(ELogLevel::Info, str, std::forward<TFmt>(args)...); }

			template<typename ... TFmt>
			void WARNING(std::format_string<TFmt...> str, TFmt&&... args) { Log(ELogLevel::Warning, str, std::forward<TFmt>(args)...); }

			template<typename ... TFmt>
			void ERROR(std::format_string<TFmt...> str, TFmt&&... args) { Log(ELogLevel::Error, str, std::forward<TFmt>(args)...); }

			template<typename ... TFmt>
			void FATAL(std::format_string<TFmt...> str, TFmt&&... args) { Log(ELogLevel::Fatal, str, std::forward<TFmt>(args)...); }

		public: // INTERFACE
			virtual ~ILogger() = default;
		protected:
			virtual void Log(const SLogMessage& msg) = 0;

		private:
			template<typename ... TFmt>
			void Log(ELogLevel level, std::format_string<TFmt...> fmtStr, TFmt&&... fmtArgs)
			{
				SLogMessage msg;
				msg.Level = level;
				msg.Timestamp = std::chrono::system_clock::now();
				msg.Source = std::source_location::current();
				msg.MessageFormatter = [fmtStr, ...args = std::forward<TFmt>(fmtArgs)]() mutable {
					return std::format(fmtStr, std::forward<TFmt>(args)...);
					};
				Log(msg);
			}
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------