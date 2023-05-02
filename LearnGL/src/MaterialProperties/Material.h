#pragma once

#include <GL/glew.h>

namespace YSAoo {
	class Material
	{
	public:
		Material();
		Material(GLfloat SpecularIntensity, GLfloat Shininess);

		void UseMaterial(GLuint SpecularIntensityLocation, GLuint ShininessLocation);

		~Material();
	private:
		GLfloat SpecularIntensity;
		GLfloat Shininess;
	};
}

