#include "DirectionalLight.h"
namespace YSAoo {
	DirectionalLight::DirectionalLight() : Light()
	{
		LightType = YLightType::YDirectionalLight;
		Direction = glm::vec3(0.0f, -1.0f, 0.0f);
		DirectionalLightStruct = {};
	}

	DirectionalLight::DirectionalLight(GLuint ShadowWidth, GLuint ShadowHeight, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat AmbientIntensity, GLfloat DiffuseIntensity)
		: Light(ShadowWidth, ShadowHeight, Red, Green, Blue, AmbientIntensity, DiffuseIntensity)
	{
		LightType = YLightType::YDirectionalLight;
		Color = glm::vec3(Red, Green, Blue);
		this->AmbientIntensity = AmbientIntensity;
		this->DiffuseIntensity = DiffuseIntensity;
		Direction = glm::vec3(0.0f, -1.0f, 0.0f);
		DirectionalLightStruct = {};

		LightProj = glm::ortho(-20.f, 20.f, -20.f, 20.f, 0.1f, 100.f);
		glm::mat4 LightProj1 =  glm::lookAt(-Direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		//PRINT_MATRIX(LightProj1);
	}

	glm::mat4 DirectionalLight::CalculateDirectionalLightTransform()
	{
		glm::mat4 LightProj1 = LightProj * glm::lookAt(-Direction, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f));
		return LightProj1;
	}

	void DirectionalLight::UseLight()
	{
		glm::mat4 ModelMatrix(1.0f);
		ModelMatrix = glm::rotate(ModelMatrix, this->GetObjectRotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, this->GetObjectRotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
		ModelMatrix = glm::rotate(ModelMatrix, this->GetObjectRotation().z, glm::vec3(0.0f, 0.0f, 1.0f));

		glm::vec3 TempDirection = Direction * glm::mat3(ModelMatrix);

		glUniform3f(DirectionalLightStruct.Base.ColorLocation, Color.x, Color.y, Color.z);
		glUniform1f(DirectionalLightStruct.Base.AmbientIntensityLocation, AmbientIntensity);
		glUniform1f(DirectionalLightStruct.Base.DiffuseIntensityLocation, DiffuseIntensity);
		glUniform3f(DirectionalLightStruct.DirectionLocation, TempDirection.x, TempDirection.y, TempDirection.z);
	}

	void DirectionalLight::CreateLightVolume()
	{
		LightVolume = new Model();
		LightVolume->CreateObject("BaseDirectionalLightVolume", YObjectType::YModel);
		LightVolume->SetTransform(glm::vec3(0.0f, 0.0f, 1.f));
		if (!LightVolume->LoadModel("Models/quad.obj")) {
			printf("Couldnt load model!\n");
		}
	}

	DirectionalLight::~DirectionalLight()
	{
	}
}