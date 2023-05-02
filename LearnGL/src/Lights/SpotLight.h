#pragma once
#include "PointLight.h"

namespace YSAoo {
    class SpotLight :
        public PointLight
    {
    public:
        SpotLight();
        SpotLight(GLuint ShadowWidth, GLuint ShadowHeight, GLfloat Near, GLfloat Far, GLfloat Red, GLfloat Green, GLfloat Blue, GLfloat AmbientIntensity, GLfloat DiffuseIntensity,
            GLfloat XPos, GLfloat YPos, GLfloat ZPos, 
            GLfloat Constant, GLfloat Linear, GLfloat Exponent,
            GLfloat XDir, GLfloat YDir, GLfloat ZDir, GLfloat Edge);

        virtual void UseLight() override;

        void SetFlash(glm::vec3 Pos, glm::vec3 Dir);

        ~SpotLight();

    private:
        glm::vec3 Direction;

        GLfloat Edge, ProcessedEdge;
    public:
        // TRY TO MAKE IT PROTECTED LATER
        typedef struct {
            YPointLightStruct Base;
            GLuint DirectionLocation;
            GLuint ProcEdgeLocation;
        } YSpotLightStruct;
        YSpotLightStruct SpotLightStruct;
    };
}

