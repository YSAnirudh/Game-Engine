#pragma once
#include "Light.h"
#include <vector>

#include "Shadows/OmniShadowMap.h"

namespace YSAoo {
    class PointLight :
        public Light
    {
    public:
        PointLight();
        PointLight(GLuint ShadowWidth, GLuint ShadowHeight, GLfloat Near, GLfloat Far, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat AmbientIntensity, GLfloat DiffuseIntensity,
            GLfloat XPos, GLfloat YPos, GLfloat ZPos, GLfloat Constant, GLfloat Linear, GLfloat Exponent);

        virtual void UseLight() override;

        virtual void CreateLightVolume() override;
        float CalcPointLightSphereScale();

        std::vector<glm::mat4> CalculateLightTransform();

        inline GLfloat GetFarPlane() const { return FarPlane; };
        inline glm::vec3 GetPosition() const { return Position; };
        inline glm::vec3 GetAttenuation() const { return glm::vec3(Constant, Linear, Exponent); };

        ~PointLight();
    protected:
        glm::vec3 Position;

        GLfloat Constant, Linear, Exponent;

        GLfloat FarPlane;
    public:
        // TRY TO MAKE IT PROTECTED LATER
        typedef struct {
            YLightStruct Base;
            GLuint PositionLocation;
            GLuint ConstantLocation;
            GLuint LinearLocation;
            GLuint ExponentLocation;
        } YPointLightStruct;
        YPointLightStruct PointLightStruct;
    };
}

