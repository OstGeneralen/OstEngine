// OstLogger - Copyright(c) 2025 Kasper Esbjörnsson (MIT License)
#pragma once
#include "OstLog/Sinks/LogSink.h"

#include <sstream>
#include <filesystem>

// ------------------------------------------------------------

namespace ost
{
	namespace log 
	{
		class CFileLogSink final : public CLogSink
		{
		public:
			CFileLogSink(std::filesystem::path logFileDirectory, std::string logFileMainName = "OstLog");
			void Log(const SLogMessage& msg) override;
			void Flush() override;
		private:
			std::stringstream _contentStream;
			std::filesystem::path _activeLogFilePath;
		};
	}
}

// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------