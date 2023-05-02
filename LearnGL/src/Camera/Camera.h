#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Managers/InputManager.h"

namespace YSAoo {
	struct CameraDirection {
		GLenum CubemapFace;
		glm::vec3 Center;
		glm::vec3 Up;
	};

	class InputManager;
	class Camera
	{
	public:
		Camera(
			glm::vec3 InitPosition,
			glm::vec3 InitUp,
			GLfloat InitYaw,
			GLfloat InitPitch, 
			GLfloat InitMoveSpeed, 
			GLfloat InitSensitivity
		);

		glm::mat4 CalculateViewMatrix();

		void CameraKeyControl(bool* keys, GLfloat DeltaTime);
		void CameraMouseControl(GLfloat XChange, GLfloat YChange);

		inline glm::vec3 GetCameraPosition() const { return CameraPosition; };
		inline glm::vec3 GetCameraDirection() const { return glm::normalize(CameraFront); };

		// Input Functions for Camera
		void OnCtrlPress(GLFWwindow* TempWindow, InputManager* MyInput);

		~Camera();
	private:
		glm::vec3 CameraPosition;
		glm::vec3 CameraUp;
		glm::vec3 CameraRight;
		glm::vec3 CameraFront;
		glm::vec3 WorldUp;

		GLfloat Yaw;
		GLfloat Pitch;
		GLfloat Roll;

		GLfloat MovementSpeed;
		GLfloat MouseSensitivity;

		void Update();
	};
}

#endif