#include <YSAoo-Engine.h>
#include "Logger/Logger.h"

class MainApp : public YSAoo::Application {
public:
	MainApp() {

	}
	~MainApp() {

	}
};

YSAoo::Application* YSAoo::CreateApplication() {
	return new MainApp();
}