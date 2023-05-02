#ifndef WINDOW_H
#define WINDOW_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "IMGUI/imgui.h"
#include "IMGUI/imgui_impl_glfw.h"
#include "IMGUI/imgui_impl_opengl3.h"

#include "Managers/InputManager.h"

namespace YSAoo {
	class InputManager;
	class Window
	{
	public:
		Window();
		int CreateWindow(GLint WindowWidth, GLint WindowHeight, const char* WindowName);

		bool WindowShouldClose();
		void SwapBuffers();

		inline GLFWwindow* GetMainWindow() { return MainWindow; };

		inline InputManager* GetInputManager() { return WindowInputManager; };

		inline GLint GetWindowWidth() { return WindowWidth; };
		inline GLint GetWindowHeight() { return WindowHeight; };
		inline const char* GetWindowName() { return WindowName; };

		inline int GetFrameBufferWidth() { return FrameBufferWidth; };
		inline int GetFrameBufferHeight() { return FrameBufferHeight; };

		inline void SetFrameBufferWidth(int FrameBufferWidth) { this->FrameBufferWidth = FrameBufferWidth; };
		inline void SetFrameBufferHeight(int FrameBufferHeight) { this->FrameBufferHeight = FrameBufferHeight; };
	private:
		GLFWwindow* MainWindow = nullptr;
		GLint WindowWidth;
		GLint WindowHeight;
		const char* WindowName;

		int FrameBufferWidth, FrameBufferHeight;

		InputManager* WindowInputManager = nullptr;
	};
}

#endif