#include "Logger.h"
namespace YSAoo {
	Logger::Logger(): loggerName("Default") {}
	Logger::Logger(std::string LoggerName)
	{
		loggerName = LoggerName;
	}
	Logger::~Logger() {}

	Logger* Logger::GetLogger(std::string LoggerName)
	{
		return new Logger(loggerName);
	}

	std::string Logger::GetName() {
		return loggerName;
	}

	void Logger::trace(std::string message)
	{
	}


}