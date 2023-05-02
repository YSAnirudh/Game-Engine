#pragma once
#include "Light.h"

#include <GL/glew.h>
#include "Common.h"

namespace YSAoo {
    class Light;
    class DirectionalLight :
        public Light
    {
    public:
        DirectionalLight();
        DirectionalLight(GLuint ShadowWidth, GLuint ShadowHeight, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat AmbientIntensity, GLfloat XDir, GLfloat YDir, GLfloat ZDir, GLfloat DiffuseIntensity);
        
        glm::mat4 CalculateDirectionalLightTransform();

        virtual void UseLight() override;
        virtual void CreateLightVolume();

        ~DirectionalLight();
    protected:
        glm::vec3 Direction;
    public:
        // TRY TO MAKE IT PROTECTED LATER
        typedef struct {
            YLightStruct Base;
            GLuint DirectionLocation;
        } YDirectionalLightStruct;
        YDirectionalLightStruct DirectionalLightStruct;
    };
}

