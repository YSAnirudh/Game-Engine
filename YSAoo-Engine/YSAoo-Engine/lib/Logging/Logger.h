#pragma once
#include <string>
namespace YSAoo {
	enum Verbosity {
		TRACE, INFO, WARN, ERROR, FATAL
	};

	class Logger
	{
	public: 
		Logger();
		Logger(std::string LoggerName);
		~Logger();
		Logger* GetLogger(std::string LoggerName);
		std::string GetName();
		void trace(std::string message);

	private:
		std::string loggerName;
		//char color;
		//Verbosity currentVerbosity = TRACE;
	};
}
