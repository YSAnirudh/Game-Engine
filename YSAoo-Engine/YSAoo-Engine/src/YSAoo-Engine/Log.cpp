#include "Log.h"

namespace YSAoo {
	std::shared_ptr<YSAoo::Logger> Log::p_CoreLogger;
	std::shared_ptr<YSAoo::Logger> Log::p_ClientLogger;

	void Log::Init() {
		p_CoreLogger = YSAoo::Logger::GetLogger("YSAoo");
		p_ClientLogger = YSAoo::Logger::GetLogger("Sandbox");
	}
}