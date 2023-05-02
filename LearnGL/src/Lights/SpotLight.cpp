#include "SpotLight.h"
namespace YSAoo {
	SpotLight::SpotLight() : PointLight()
	{
		LightType = YLightType::YSpotLight;
		Direction = glm::vec3(0.0f, -1.0f, 0.0f);
		Edge = 0.0f;
		ProcessedEdge = 0.0f;
		SpotLightStruct = {};
	}

	SpotLight::SpotLight(GLuint ShadowWidth, GLuint ShadowHeight, GLfloat Near, GLfloat Far, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat AmbientIntensity, GLfloat DiffuseIntensity,
		GLfloat XPos, GLfloat YPos, GLfloat ZPos, GLfloat Constant, GLfloat Linear, GLfloat Exponent, 
		GLfloat XDir, GLfloat YDir, GLfloat ZDir, GLfloat Edge)
		: PointLight(ShadowWidth, ShadowHeight, Near, Far, Red, Green, Blue, AmbientIntensity, DiffuseIntensity, XPos, YPos, ZPos, Constant, Linear, Exponent)
	{
		LightType = YLightType::YSpotLight;
		Direction = glm::normalize(glm::vec3(XDir, YDir, ZDir));
		this->Edge = Edge;
		this->ProcessedEdge = cosf(glm::radians(Edge));
		SpotLightStruct = {};
	}

	void SpotLight::UseLight()
	{
		glUniform3f(SpotLightStruct.Base.Base.ColorLocation, Color.x, Color.y, Color.z);
		glUniform1f(SpotLightStruct.Base.Base.AmbientIntensityLocation, AmbientIntensity);
		glUniform1f(SpotLightStruct.Base.Base.DiffuseIntensityLocation, DiffuseIntensity);
		glUniform3f(SpotLightStruct.Base.PositionLocation, Position.x, Position.y, Position.z);
		glUniform1f(SpotLightStruct.Base.ConstantLocation, Constant);
		glUniform1f(SpotLightStruct.Base.LinearLocation, Linear);
		glUniform1f(SpotLightStruct.Base.ExponentLocation, Exponent);
		glUniform3f(SpotLightStruct.DirectionLocation, Direction.x, Direction.y, Direction.z);
		glUniform1f(SpotLightStruct.ProcEdgeLocation, ProcessedEdge);
	}

	void SpotLight::SetFlash(glm::vec3 Pos, glm::vec3 Dir)
	{
		Position = Pos;
		Direction = glm::normalize(Dir);
	}

	SpotLight::~SpotLight()
	{
	}
}