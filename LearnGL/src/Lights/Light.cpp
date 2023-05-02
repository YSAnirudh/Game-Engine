#include "Light.h"
namespace YSAoo {
	Light::Light()
	{
		Color = glm::vec3(1.0f, 1.0f, 1.0f);
		this->AmbientIntensity = 1.0f;
		this->DiffuseIntensity = 0.0f;
		LightStruct = {};
		LightProj = glm::mat4();
	}

	Light::Light(GLuint ShadowWidth, GLuint ShadowHeight, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat AmbientIntensity, GLfloat DiffuseIntensity)
	{
		LightShadowMap = new ShadowMap();
		LightShadowMap->Init(ShadowWidth, ShadowHeight);
		Color = glm::vec3(Red, Green, Blue);
		this->AmbientIntensity = AmbientIntensity;
		this->DiffuseIntensity = DiffuseIntensity;
		LightStruct = {};
		LightProj = glm::mat4();
	}

	void Light::UseLight()
	{
		/*glUniform3f(LightStruct.ColorLocation, Color.x, Color.y, Color.z);
		glUniform1f(LightStruct.AmbientIntensityLocation, AmbientIntensity);
		glUniform1f(LightStruct.DiffuseIntensityLocation, DiffuseIntensity);*/
	}

	void Light::SetShadowProperties(GLfloat ShadowWidth, GLfloat ShadowHeight)
	{
		LightShadowMap = new ShadowMap();
		LightShadowMap->Init((unsigned int)ShadowWidth, (unsigned int)ShadowHeight);
	}

	Light::~Light()
	{
	}
}