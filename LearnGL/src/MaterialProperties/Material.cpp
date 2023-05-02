#include "Material.h"
namespace YSAoo {
	Material::Material()
	{
		this->SpecularIntensity = 0.0f;
		this->Shininess = 0.0f;
	}

	Material::Material(GLfloat SpecularIntensity, GLfloat Shininess)
	{
		this->SpecularIntensity = SpecularIntensity;
		this->Shininess = Shininess;
	}

	void Material::UseMaterial(GLuint SpecularIntensityLocation, GLuint ShininessLocation)
	{
		glUniform1f(SpecularIntensityLocation, SpecularIntensity);
		glUniform1f(ShininessLocation, Shininess);
	}

	Material::~Material()
	{
	}
}