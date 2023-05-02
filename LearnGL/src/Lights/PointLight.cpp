#include "PointLight.h"
namespace YSAoo {
	PointLight::PointLight() : Light()
	{
		LightType = YLightType::YPointLight;
		this->Position = glm::vec3(0.0f, 0.0f, 0.0f);
		this->Constant = 1.0f;
		this->Linear = 0.0f;
		this->Exponent = 0.0f;
		PointLightStruct = {};

		FarPlane = 0.0f;
	}
	PointLight::PointLight(GLuint ShadowWidth, GLuint ShadowHeight, GLfloat Near, GLfloat Far, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat AmbientIntensity, GLfloat DiffuseIntensity,
		GLfloat XPos, GLfloat YPos, GLfloat ZPos, GLfloat Constant, GLfloat Linear, GLfloat Exponent)
		:Light(ShadowWidth, ShadowHeight, Red, Green, Blue, AmbientIntensity, DiffuseIntensity)
	{
		LightType = YLightType::YPointLight;
		this->Position = glm::vec3(XPos, YPos, ZPos);
		this->Constant = Constant;
		this->Linear = Linear;
		this->Exponent = Exponent;
		PointLightStruct = {};

		FarPlane = Far;

		float Aspect = (float)ShadowWidth / (float)ShadowHeight;
		LightProj = glm::perspective(glm::radians(90.f), Aspect, Near, Far);

		LightShadowMap = new OmniShadowMap();
		LightShadowMap->Init(ShadowWidth, ShadowHeight);
	}

	void PointLight::UseLight()
	{
		//printf("%d\n", PointLightStruct.Base.ColorLocation);
		glUniform3f(PointLightStruct.Base.ColorLocation, Color.x, Color.y, Color.z);
		glUniform1f(PointLightStruct.Base.AmbientIntensityLocation, AmbientIntensity);
		glUniform1f(PointLightStruct.Base.DiffuseIntensityLocation, DiffuseIntensity);
		glUniform3f(PointLightStruct.PositionLocation, Position.x, Position.y, Position.z);
		glUniform1f(PointLightStruct.ConstantLocation, Constant);
		glUniform1f(PointLightStruct.LinearLocation, Linear);
		glUniform1f(PointLightStruct.ExponentLocation, Exponent);

	}

	void PointLight::CreateLightVolume()
	{
		LightVolume = new Model();
		LightVolume->CreateObject("BasePointLightVolume", YObjectType::YModel);
		if (!LightVolume->LoadModel("Models/sphere.obj")) {
			printf("Couldnt load model!\n");
		}
		LightVolume->SetTransform(Position, glm::vec3(0.0f), glm::vec3(CalcPointLightSphereScale()));
	}

	float PointLight::CalcPointLightSphereScale()
	{
		float MaxChannel = fmax(fmax(GetColor().x, GetColor().y), GetColor().z);

		glm::vec3 Atten = GetAttenuation();
		float ret = (-Atten.y + sqrtf(Atten.y * Atten.y - 4 * Atten.z * (Atten.x - (256.f * 0.05f) * MaxChannel * GetIntensity().y)))
			/
			(2 * Atten.z);
		return ret;
	}

	std::vector<glm::mat4> PointLight::CalculateLightTransform()
	{
		std::vector<glm::mat4> LightMatrices;
		LightMatrices.push_back(LightProj * glm::lookAt(Position, Position + glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		LightMatrices.push_back(LightProj * glm::lookAt(Position, Position + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		LightMatrices.push_back(LightProj * glm::lookAt(Position, Position + glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		LightMatrices.push_back(LightProj * glm::lookAt(Position, Position + glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)));
		LightMatrices.push_back(LightProj * glm::lookAt(Position, Position + glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		LightMatrices.push_back(LightProj * glm::lookAt(Position, Position + glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
		return LightMatrices;
	}

	PointLight::~PointLight()
	{
	}
}