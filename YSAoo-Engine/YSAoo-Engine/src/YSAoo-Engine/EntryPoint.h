#pragma once
#include "Application.h"
#include "Log.h"

#ifdef YSA_PLATFORM_WINDOWS

extern YSAoo::Application* YSAoo::CreateApplication();

int main(int argc, char** argv) {
	YSAoo::Log::Init();
	//YSAoo_CLIENT_ERROR("Hello");

	YSAoo::Application* app = YSAoo::CreateApplication();
	app->Run();
	delete app;
}

#endif // YSA_PLATFORM_WINDOWS
