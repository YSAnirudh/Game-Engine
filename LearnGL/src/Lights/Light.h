#ifndef LIGHT_H
#define LIGHT_H
#include "Objects/GameObject.h"
#include "Meshes/Model.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shadows/ShadowMap.h"

namespace YSAoo {
	enum class YLightType {
		YDirectionalLight,
		YPointLight,
		YSpotLight,
		YDefault
	};
	class Model;
	class Light : public GameObject
	{
	public:
		Light();
		Light(GLuint SWidth, GLuint SHeight, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat AmbientIntensity,
			GLfloat DiffuseIntensity);

		virtual void UseLight();

		virtual void CreateLightVolume() {};

		inline YLightType GetLightType() const { return LightType; };
		inline void SetLightType(YLightType LightType) { this->LightType = LightType; };

		void SetShadowProperties(GLfloat ShadowWidth, GLfloat ShadowHeight);

		inline ShadowMap* GetShadowMap() const { return LightShadowMap; };

		inline glm::vec3 GetColor() const { return Color; };
		inline glm::vec2 GetIntensity() const { return glm::vec2(AmbientIntensity, DiffuseIntensity); };
		inline Model* GetLightVolume() const { return LightVolume; };

		~Light();

	protected:
		glm::vec3 Color;
		GLfloat AmbientIntensity;
		GLfloat DiffuseIntensity;

		Model* LightVolume = nullptr;

		glm::mat4 LightProj;

		ShadowMap* LightShadowMap = nullptr;

		YLightType LightType = YLightType::YDefault;

	public:
		// TRY TO MAKE IT PROTECTED LATER
		typedef struct {
			GLuint AmbientIntensityLocation;
			GLuint DiffuseIntensityLocation;
			GLuint ColorLocation;
		} YLightStruct;

		YLightStruct LightStruct;
	};
}

#endif