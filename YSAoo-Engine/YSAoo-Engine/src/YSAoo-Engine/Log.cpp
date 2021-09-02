#include "Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
namespace YSAoo {
	std::shared_ptr<spdlog::logger> Log::p_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::p_ClientLogger;

	void Log::Init() {
		spdlog::set_pattern("%^[%T] %n: %v%$");
		p_CoreLogger = spdlog::stdout_color_mt("YSAoo-Engine");
		p_ClientLogger = spdlog::stdout_color_mt("Sandbox");
	}
}