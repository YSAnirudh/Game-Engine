#pragma once
#include "Application.h"

#ifdef YSA_PLATFORM_WINDOWS

extern YSAoo::Application* YSAoo::CreateApplication();

int main(int argc, char** argv) {
	YSAoo::Application* app = YSAoo::CreateApplication();
	app->Run();
	delete app;
}

#endif // YSA_PLATFORM_WINDOWS
