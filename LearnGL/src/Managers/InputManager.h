#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include "Windows/Window.h"

namespace YSAoo {
	class InputManager
	{
	public:
		InputManager();

		void SetCallbacksForWindow(GLFWwindow* MainWindow);

		/// <summary>
		///  100% Please change this
		/// </summary>
		/// <returns></returns>
		inline bool* GetKeys() { return Keys; };

		inline GLfloat GetMouseXChange() { GLfloat change = MouseChangeX; MouseChangeX = 0.f; return change; };
		inline GLfloat GetMouseYChange() { GLfloat change = MouseChangeY; MouseChangeY = 0.f; return change; };

		~InputManager();
	private:
		bool Keys[1024];

		GLfloat LastMousePosX;
		GLfloat LastMousePosY;
		GLfloat MouseChangeX = 0.f;
		GLfloat MouseChangeY = 0.f;
		bool MouseFirstMoved;

	private:
		static void HandleKeyboardInput(GLFWwindow* Window, int Key, int Code, int Action, int Mode);
		static void HandleMouseInput(GLFWwindow* Window, double xPos, double yPos);
	};
}

#endif