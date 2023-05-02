#ifndef FORWARD_SHADER_H
#define FORWARD_SHADER_H

#include "Shader.h"

namespace YSAoo {
    class ForwardShader :
        public Shader
    {
    public:
        ForwardShader();

        virtual void GetLocationsForLighting(Light* MainLight) override;

        void SetLightCounts();

        void ResetShaderLightCount();

        ~ForwardShader();
    protected:
        int DirLightCount = 0, PointLightCount = 0, SpotLightCount = 0;
        virtual int CompileProgram() override;

        GLuint UniformDirectionalLightCount, UniformSpotLightCount, UniformPointLightCount;

        struct  {
            GLuint UniformColor;
            GLuint UniformAmbientIntensity;
            GLuint UniformDiffuseIntensity;
            GLuint UniformDirection;
        } UniformDirectionalLight[MAX_SPOT_LIGHTS];

        struct {
            GLuint UniformColor;
            GLuint UniformAmbientIntensity;
            GLuint UniformDiffuseIntensity;
            GLuint UniformPosition;
            GLuint UniformConstant;
            GLuint UniformLinear;
            GLuint UniformExponent;
        } UniformPointLight[MAX_POINT_LIGHTS];

        struct {
            GLuint UniformColor;
            GLuint UniformAmbientIntensity;
            GLuint UniformDiffuseIntensity;
            GLuint UniformPosition;
            GLuint UniformConstant;
            GLuint UniformLinear;
            GLuint UniformExponent;
            GLuint UniformDirection;
            GLuint UniformEdge;
        } UniformSpotLight[MAX_SPOT_LIGHTS];

    };
}

#endif