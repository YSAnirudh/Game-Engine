#pragma once
#include "Application.h"
#include "Logger/Logger.h"
#ifdef YSA_PLATFORM_WINDOWS

extern YSAoo::Application* YSAoo::CreateApplication();

int main(int argc, char** argv) {
	YSAoo::Logger* mainLogger = YSAoo::Logger::GetLogger("YSAoo's Logger");


	YSAoo::Application* app = YSAoo::CreateApplication();
	mainLogger->trace("Hello");
	mainLogger->trace("Hello2");
	app->Run();
	delete app;
	delete mainLogger;
}

#endif // YSA_PLATFORM_WINDOWS
