#include "GLInit.h"

int main() {

	YSAoo::GLInit* OpenGL = new YSAoo::GLInit(WINDOW_WIDTH, WINDOW_HEIGHT, "Main Window");

	OpenGL->MainLoop();

	return 0;
}