#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Lights/DirectionalLight.h"
#include "Lights/SpotLight.h"
#include "Lights/PointLight.h"

#include "Common.h"
#include "RenderingCommons.h"

namespace YSAoo {
	enum class YShaderType {
		YLightingShader,
		YDefault
	};
	class Shader
	{
	public:
		Shader();
		//Shader()

		void CreateShaderFromString(const char* VertexCode, const char* FragmentCode);
		void CreateFromFiles(const char* VertexShaderLocation, const char* FragmentShaderLocation, const char* GeometryShaderLocation);
		void CreateFromFiles(const char* VertexShaderLocation, const char* FragmentShaderLocation);

		void Validate();

		std::string ReadFromFile(const char* Location);

		void UseShader();
		void ClearShader();

		virtual void GetLocationsForLighting(Light* MainLight);

		void SetTexture(GLuint TextureUnit);
		void SetDirectionalShadowMap(GLuint TextureUnit);
		void SetDirectionalLightTransform(glm::mat4* Transform);
		void SetLightMatrices(std::vector<glm::mat4> LightMatrices);
		void SetGSamplers(GLuint TextureUnitPos, GLuint TextureUnitColor, GLuint TextureUnitNorm);
		void SetScreenSize(const glm::vec2& ScreenSize);
		void SetProjectionView(const glm::mat4& ProjectionMatrix, const glm::mat4& ViewMatrix);
		void SetEyePosition(const glm::vec3& CameraPosition);
		void SetOmniShadowSpecs(const glm::vec3& PointLightPosition, const GLfloat& FarPlane);

		inline GLuint GetProjectionMatrixLocation() const { return UniformProjectionMatrix; };
		inline GLuint GetModelMatrixLocation() const { return UniformModelMatrix; };
		inline GLuint GetViewMatrixLocation() const { return UniformViewMatrix; };
		inline GLuint GetSpecularIntensityLocation() const { return UniformSpecularIntensity; };
		inline GLuint GetShininessLocation() const { return UniformShininess; };
		inline GLuint GetEyePositionLocation() const { return UniformEyePositionLocation; };
		inline GLuint GetOmniLightPosLocation() const { return UniformOmniLightPos; };
		inline GLuint GetFarPlaneLocation() const { return UniformFarPlane; };


		~Shader();
		GLuint UniformDirectionalLightTransform;
		GLuint UniformOmniLightPos, UniformFarPlane;

		GLuint UniformLightMatrices[6];
	protected:
		int CompileShaders(const char* VertexCode, const char* FragmentCode, const char* GeometryCode);
		int CompileShaders(const char* VertexCode, const char* FragmentCode);
		virtual int CompileProgram();
		int CompileShadersAndInit(const char* VertexCode, const char* FragmentCode);
		int AddShader(GLuint ShaderProgram, const char* ShaderCode, GLenum ShaderType);

		GLuint ShaderID;

		GLuint UniformModelMatrix;
		GLuint UniformViewMatrix;
		GLuint UniformProjectionMatrix;

		GLuint UniformSpecularIntensity;
		GLuint UniformShininess;

		GLuint UniformEyePositionLocation;

		GLuint UniformTexture;
		GLuint UniformDirectionalShadowMap;

		GLuint UniformGPositionMap, UniformGColorMap, UniformGNormalMap;
		GLuint UniformScreenSize;

		struct {
			GLuint shadowMap;
			GLuint farPlane;
		} uniformOmniShadowMaps;

	protected:
		YShaderType ShaderType = YShaderType::YDefault;
	};
}


#endif