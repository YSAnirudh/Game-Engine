#include "Camera.h"
namespace YSAoo {
	Camera::Camera(glm::vec3 InitPosition, glm::vec3 InitUp, GLfloat InitYaw, GLfloat InitPitch, GLfloat InitMoveSpeed, GLfloat InitSensitivity)
	{
		CameraPosition = InitPosition;
		WorldUp = InitUp;
		Yaw = InitYaw;
		Pitch = InitPitch;

		CameraFront = glm::vec3(0.f, 0.f, -1.0f);

		MovementSpeed = InitMoveSpeed;
		MouseSensitivity = InitSensitivity;

		Update();
	}

	glm::mat4 Camera::CalculateViewMatrix()
	{
		return glm::lookAt(CameraPosition, CameraPosition + CameraFront, CameraUp);
	}

	void Camera::CameraKeyControl(bool* keys, GLfloat DeltaTime)
	{
		GLfloat Velocity = MovementSpeed * DeltaTime;
		if (keys[GLFW_KEY_W]) {
			CameraPosition += CameraFront * Velocity;
		}
		if (keys[GLFW_KEY_S]) {
			CameraPosition -= CameraFront * Velocity;
		}
		if (keys[GLFW_KEY_A]) {
			CameraPosition -= CameraRight * Velocity;
		}
		if (keys[GLFW_KEY_D]) {
			CameraPosition += CameraRight * Velocity;
		}
		if (keys[GLFW_KEY_E]) {
			CameraPosition += CameraUp * Velocity;
		}
		if (keys[GLFW_KEY_Q]) {
			CameraPosition -= CameraUp * Velocity;
		}
	}

	void Camera::CameraMouseControl(GLfloat XChange, GLfloat YChange)
	{
		YChange *= MouseSensitivity;
		XChange *= MouseSensitivity;

		Yaw += XChange;
		Pitch += YChange;

		Pitch = glm::clamp(Pitch, -89.99f, 89.99f);

		Update();
	}

	void Camera::OnCtrlPress(GLFWwindow* TempWindow, InputManager* MyInput)
	{
		if (glfwGetMouseButton(TempWindow, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
			CameraMouseControl(MyInput->GetMouseXChange(), MyInput->GetMouseYChange());
		}
	}

	void Camera::Update()
	{
		CameraFront.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		CameraFront.y = sin(glm::radians(Pitch));
		CameraFront.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

		CameraFront = glm::normalize(CameraFront);

		CameraRight = glm::normalize(glm::cross(CameraFront, WorldUp));
		CameraUp = glm::normalize(glm::cross(CameraRight, CameraFront));
	}


	Camera::~Camera()
	{
	}
}