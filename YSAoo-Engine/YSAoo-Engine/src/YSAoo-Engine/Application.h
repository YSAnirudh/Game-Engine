#pragma once
#include "Core.h"

namespace YSAoo {

	class YSAoo_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	YSAoo::Application* CreateApplication();

}