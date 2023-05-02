#ifndef RENDERING_H
#define RENDERING_H

#include "Shaders/Shader.h"
#include <vector>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace YSAoo {
	class Rendering
	{
	public:
		Rendering();

		virtual void AddShader(const char* VertexShaderLocation, const char* FragmentShaderLocation, const char* GeometryShaderLocation = "");

		~Rendering();
	protected:
		GLuint UniformModel = 0, UniformSpecularIntensity = 0, UniformShininess = 0;
		GLint WindowWidth, WindowHeight;

		std::vector<Shader*> ShaderList;
		glm::mat4 Projection, View;
		glm::vec3 CameraPosition;
	
	public:
		inline void SetProjectionView(const glm::mat4& Projection, const glm::mat4& View) {
			this->Projection = Projection;
			this->View = View;
		}

		inline void SetCameraPosition(const glm::vec3 CameraPosition) {
			this->CameraPosition = CameraPosition;
		}
	};
}

#endif