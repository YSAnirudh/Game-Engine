#pragma once
#include "PointLight.h"
class SpotLight :
    public PointLight {
public:
    SpotLight();

    SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
        GLfloat xPos, GLfloat yPos, GLfloat zPos,
        GLfloat xDirection, GLfloat yDirection, GLfloat zDirection,
        GLfloat cons, GLfloat lin, GLfloat exp,
        GLfloat edg);
    void useLight(GLuint ambientIntensityLocation, GLuint colorLocation,
        GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint directionLocation,
        GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint edgeLocation);

    void SetFlash(glm::vec3 pos, glm::vec3 dir);

    ~SpotLight();
private:
    glm::vec3 direction;

    GLfloat edge, procEdge;
};

