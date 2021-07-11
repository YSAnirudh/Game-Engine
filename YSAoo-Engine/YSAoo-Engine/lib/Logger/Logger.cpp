#include "Logger.h"
#include <iostream>
#include <ctime>
#include <chrono>
#include <memory>
namespace YSAoo {
	Logger::Logger(): loggerName("Default") {}
	Logger::Logger(std::string LoggerName)
	{
		loggerName = LoggerName;
	}
	Logger::~Logger() {}

	std::shared_ptr<Logger> Logger::GetLogger(std::string LoggerName)
	{
		auto logger = std::make_shared<Logger>(LoggerName);
		logger->SetName(LoggerName);
		return logger;
	}

	std::string Logger::GetName() {
		return loggerName;
	}

	void Logger::trace(std::string message) {
		auto timeNow = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::cout << "\033[1;31mbold red text\033[0m\n";
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

	void Logger::SetName(std::string LoggerName)
	{
		loggerName = LoggerName;
	}


}