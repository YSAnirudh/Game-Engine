#include "InputManager.h"
namespace YSAoo {
	InputManager::InputManager()
	{
		for (int i = 0; i < 1024; i++) {
			Keys[i] = 0;
		}
	}

	InputManager::~InputManager()
	{
	}

	void InputManager::HandleKeyboardInput(GLFWwindow* PassWindow, int Key, int Code, int Action, int Mode)
	{
		Window* MainWindow = static_cast<Window*>(glfwGetWindowUserPointer(PassWindow));

		if (Key == GLFW_KEY_ESCAPE && Action == GLFW_PRESS) {
			glfwSetWindowShouldClose(PassWindow, GL_TRUE);
		}

		if (Key >= 0 && Key < 1024) {
			if (Action == GLFW_PRESS) {
				MainWindow->GetInputManager()->Keys[Key] = true;
			}
			else if (Action == GLFW_RELEASE) {
				MainWindow->GetInputManager()->Keys[Key] = false;
			}
		}
	}
	
	void InputManager::HandleMouseInput(GLFWwindow* PassWindow, double xPos, double yPos)
	{
		Window* MainWindow = static_cast<Window*>(glfwGetWindowUserPointer(PassWindow));

		if (MainWindow->GetInputManager()->MouseFirstMoved) {
			MainWindow->GetInputManager()->LastMousePosX = (GLfloat)xPos;
			MainWindow->GetInputManager()->LastMousePosY = (GLfloat)yPos;
			MainWindow->GetInputManager()->MouseFirstMoved = false;
		}

		MainWindow->GetInputManager()->MouseChangeX = (GLfloat)xPos - MainWindow->GetInputManager()->LastMousePosX;
		MainWindow->GetInputManager()->MouseChangeY = MainWindow->GetInputManager()->LastMousePosY - (GLfloat)yPos;

		MainWindow->GetInputManager()->LastMousePosX = (GLfloat)xPos;
		MainWindow->GetInputManager()->LastMousePosY = (GLfloat)yPos;
	}

	void InputManager::SetCallbacksForWindow(GLFWwindow* MainWindow)
	{
		glfwSetKeyCallback(MainWindow, HandleKeyboardInput);
		glfwSetCursorPosCallback(MainWindow, HandleMouseInput);
	}
}
