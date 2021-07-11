#pragma once
#include "Application.h"
#include "Logger/Logger.h"
#include "Log.h"

#ifdef YSA_PLATFORM_WINDOWS

extern YSAoo::Application* YSAoo::CreateApplication();

int main(int argc, char** argv) {
	YSAoo::Log::Init();

	YSAoo::Application* app = YSAoo::CreateApplication();
	YSAoo_CORE_FATAL("Hello threer %d");
	YSAoo::Log::GetClientLogger()->trace("Hello2");
	app->Run();
	delete app;
}

#endif // YSA_PLATFORM_WINDOWS
