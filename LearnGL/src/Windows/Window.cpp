#include "Window.h"
namespace YSAoo {
	Window::Window()
	{
		MainWindow = nullptr;
		WindowWidth = 0;
		WindowHeight = 0;
		WindowName = "";

		FrameBufferWidth = 0;
		FrameBufferHeight = 0;
	}

	int YSAoo::Window::CreateWindow(GLint WindowWidth, GLint WindowHeight, const char* WindowName)
	{
		this->WindowWidth = WindowWidth;
		this->WindowHeight = WindowHeight;
		this->WindowName = WindowName;

		MainWindow = glfwCreateWindow(WindowWidth, WindowHeight, WindowName, NULL, NULL);
		if (!MainWindow) {
			printf("Cannot Initialize Window!!\n");
			glfwTerminate();
			return 1;
		}

		// Getting frame buffers
		glfwGetFramebufferSize(MainWindow, &FrameBufferWidth, &FrameBufferHeight);
		glfwMakeContextCurrent(MainWindow);

		WindowInputManager = new InputManager();
		glfwSetWindowUserPointer(MainWindow, this);

		WindowInputManager->SetCallbacksForWindow(MainWindow);

		return 0;
	}
	bool Window::WindowShouldClose()
	{
		return glfwWindowShouldClose(this->MainWindow);
	}
	void Window::SwapBuffers()
	{
		if (MainWindow) {
			glfwSwapBuffers(MainWindow);
		}
	}
}