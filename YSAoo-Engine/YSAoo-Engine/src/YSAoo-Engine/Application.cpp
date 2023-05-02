#include "YSApch.h"
#include "Application.h"
#include "Events/ApplicationEvent.h"
#include "Log.h"

namespace YSAoo {

	Application::Application() {}
	Application::~Application() {}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		YSAoo_CORE_TRACE(e);
		while (true);
	}

}