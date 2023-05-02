#pragma once
#include "Light.h"
class PointLight :
    public Light {
public:
    PointLight();
    PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat aIntensity, GLfloat dIntensity,
        GLfloat xPos, GLfloat yPos, GLfloat zPos,
        GLfloat cons, GLfloat lin, GLfloat exp);
    void useLight(GLuint ambientIntensityLocation, GLuint colorLocation,
        GLuint diffuseIntensityLocation, GLuint positionLocation,
        GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);


    ~PointLight();
protected:
    glm::vec3 position;

    //For Quadratic Equation
    GLfloat constant, linear, exponent;
};

