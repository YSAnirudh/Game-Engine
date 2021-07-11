#pragma once
#include <memory>
#include <Logger/Logger.h>
namespace YSAoo {
	class YSAoo_API Log
	{
	public:
		static void Init();
	public:
		static std::shared_ptr<YSAoo::Logger> GetCoreLogger() { return p_CoreLogger; };
		static std::shared_ptr<YSAoo::Logger> GetClientLogger() { return p_ClientLogger; };
	private:
		static std::shared_ptr<YSAoo::Logger> p_CoreLogger;
		static std::shared_ptr<YSAoo::Logger> p_ClientLogger;
	};
}

// CORE Logging MACROS
#define YSAoo_CORE_TRACE(...)    ::YSAoo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define YSAoo_CORE_INFO(...)     ::YSAoo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define YSAoo_CORE_WARN(...)     ::YSAoo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define YSAoo_CORE_ERROR(...)    ::YSAoo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define YSAoo_CORE_FATAL(...)    ::YSAoo::Log::GetCoreLogger()->fatal(__VA_ARGS__)
// CLIENT Logging MACROS
#define YSAoo_CLIENT_TRACE(...)  ::YSAoo::Log::GetClientLogger()->trace(__VA_ARGS__)
#define YSAoo_CLIENT_INFO(...)   ::YSAoo::Log::GetClientLogger()->info(__VA_ARGS__)
#define YSAoo_CLIENT_WARN(...)   ::YSAoo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define YSAoo_CLIENT_ERROR(...)  ::YSAoo::Log::GetClientLogger()->error(__VA_ARGS__)
#define YSAoo_CLIENT_FATAL(...)  ::YSAoo::Log::GetClientLogger()->fatal(__VA_ARGS__)
