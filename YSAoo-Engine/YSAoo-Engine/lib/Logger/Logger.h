#pragma once
#include "Core.h"
#include <string>
#include <memory>
namespace YSAoo {
	enum Verbosity {
		TRACE, INFO, WARN, ERROR, FATAL
	};

	class YSAoo_API Logger
	{
	public: 
		Logger();
		Logger(std::string LoggerName);
		~Logger();
		static std::shared_ptr<Logger> GetLogger(std::string LoggerName);
		std::string GetName();
		void SetName(std::string LoggerName);
		void trace(std::string message);
		void info(std::string message);
		void warn(std::string message);
		void error(std::string message);
		void fatal(std::string message);
	private:
		std::string loggerName;
		//char color;
		//Verbosity currentVerbosity = TRACE;
	};
}
