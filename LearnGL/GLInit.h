#ifndef GLINIT_H
#define GLINIT_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

#include <vector>
#include <iostream>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Windows/Window.h"
#include "Windows/Layers/ImGuiLayer.h"
#include "Meshes/Mesh.h"
#include "Shaders/Shader.h"
#include "Managers/InputManager.h"
#include "Camera/Camera.h"
#include "Managers/ObjectManager.h"
#include "Lights/DirectionalLight.h"
#include "Lights/PointLight.h"
#include "Lights/SpotLight.h"
#include "Shaders/GBufferShader.h"
#include "RenderingTechniques/ForwardRendering.h"
#include "RenderingTechniques/DeferredRendering.h"

#include "Camera/Skybox.h"

#include "Common.h"

#include "RenderingCommons.h"

namespace YSAoo {
	class Shader;
	class ForwardRendering;
	class DeferredRendering;
	class GLInit
	{
	public:
		GLInit();
		GLInit(const int WindowWidth, const int WindowHeight, const char* WindowName);

		int MainLoop();

		int InitializeGLFW();
		int InitializeGLEW();

		// TEMP FUNCTIONS
		void CalcAverageNormals(unsigned int* indices, unsigned int indexCount, GLfloat* vertices, unsigned int vertexCount, unsigned int vLength, unsigned int normalOffset);

		static void glfwError(int id, const char* description)
		{
			printf("%s\n", description);
		}

		~GLInit();
	protected:

	private:
		GLfloat DeltaTime = 0.0f;
		GLfloat LastTime = 0.0f;

		ObjectManager* MainObjectManager = nullptr;

		std::vector<Shader*> ShaderList;

		Camera* MainCamera = nullptr;
		Window* MainWindow = nullptr;

		Skybox* MainSkybox = nullptr;

		ForwardRendering* ForwardRenderer = nullptr;
		DeferredRendering* DeferredRenderer = nullptr;

		GLuint UniformModel = 0, UniformProjection = 0, UniformView = 0, UniformAmbientColor = 0,
			UniformAmbientIntensity = 0, UniformDirection = 0, UniformDiffuseIntensity = 0,
			UniformSpecularIntensity = 0, UniformShininess = 0, UniformEyePosition = 0,
			UniformOmniLightPos = 0, UniformFarPlane = 0;
	};
}

#endif