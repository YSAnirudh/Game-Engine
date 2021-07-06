#include "Logger.h"
#include <iostream>
#include <ctime>
#include <chrono>

namespace YSAoo {
	Logger::Logger(): loggerName("Default") {}
	Logger::Logger(std::string LoggerName)
	{
		loggerName = LoggerName;
	}
	Logger::~Logger() {}

	Logger* Logger::GetLogger(std::string LoggerName)
	{
		Logger* logger = new Logger();
		logger->setName(LoggerName);
		return logger;
	}

	std::string Logger::GetName() {
		return loggerName;
	}

	void Logger::trace(std::string message) {
		auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "[" << loggerName << "]" << " " << timeNow << " " << ":" << message << std::endl;
	}

	void Logger::info(std::string message) {
		auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "[" << loggerName << "]" << " " << timeNow << " " << ":" << message << std::endl;
	}

	void Logger::warn(std::string message) {
		auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "[" << loggerName << "]" << " " << timeNow << " " << ":" << message << std::endl;
	}

	void Logger::error(std::string message) {
		auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "[" << loggerName << "]" << " " << timeNow << " " << ":" << message << std::endl;
	}

	void Logger::fatal(std::string message) {
		auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "[" << loggerName << "]" << " " << timeNow << " " << ":" << message << std::endl;
	}

	void Logger::setName(std::string LoggerName)
	{
	}


}