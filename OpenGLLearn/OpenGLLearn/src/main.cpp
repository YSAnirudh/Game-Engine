#define STB_IMAGE_IMPLEMENTATION

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../Mesh.h"
#include "../Shader.h"
#include "../Window.h"
#include "../Camera.h"
#include "../Texture.h"
#include "../DirectionalLight.h"
#include "../Material.h"
#include "../PointLight.h"
#include "../SpotLight.h"

#include "../CommonValues.h"


const float toRadians = 3.14159265f / 180.0f;

// Need more for more objects
GLuint shader;

std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Window mainWindow;
Camera mainCamera;

Texture brickTexture;
Texture dirtTexture;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_POINT_LIGHTS];

Material shinyMaterial;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex Shader
static const char* vShader = "src/Shaders/shader.vert";

// Fragment Shader
static const char* fShader = "src/Shaders/shader.frag";

void CalcAverageNormals(unsigned int *indices, unsigned int indexCount, GLfloat* vertices, unsigned int vertexCount, unsigned int vLength, unsigned int normalOffset) {
	for (size_t i = 0; i < indexCount; i += 3) {
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;

		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);

		glm::vec3 tempNormal = glm::normalize(glm::cross(v1, v2));
		in0 += normalOffset;
		in1 += normalOffset;
		in2 += normalOffset;

		vertices[in0] += tempNormal.x; vertices[in0 + 1] += tempNormal.y; vertices[in0 + 2] += tempNormal.z;
		vertices[in1] += tempNormal.x; vertices[in1 + 1] += tempNormal.y; vertices[in1 + 2] += tempNormal.z;
		vertices[in2] += tempNormal.x; vertices[in2 + 1] += tempNormal.y; vertices[in2 + 2] += tempNormal.z;
	}
	
	for (size_t i = 0; i < vertexCount/vLength; i++) {
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}

void CreateObjects() {
	unsigned int indices[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};

	GLfloat vertices[] = {
		-1.0f, -1.0f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
		1.0f, -1.0f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f,
	};

	GLfloat floorVertices[] = {
		10.0f, -1.0f, -10.0f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, -1.0f, 10.0f,			1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		-10.0f, -1.0f, 10.0f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-10.0f, -1.0f, -10.0f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
	};

	unsigned int floorIndices[] = {
		0,3,1,
		1,3,2,
	};

	CalcAverageNormals(indices, 12, vertices, 32, 8, 5);

	Mesh* object = new Mesh();
	object->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(object);

	object = new Mesh();
	object->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(object);
}

void CreateShaders() {
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(shader1);
}

int main() {
	mainWindow = Window(1366, 768);
	mainWindow.initialize();
	
	CreateObjects();
	CreateShaders();
	
	mainCamera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.1f);
	
	brickTexture = Texture("brick.png");
	brickTexture.LoadTextureAlpha();
	dirtTexture = Texture("dirt.png");
	dirtTexture.LoadTextureAlpha();

	mainLight = DirectionalLight(
		1.0f, 1.0f, 1.0f, 
		0.2f, 0.8f,
		2.0f, -1.0f, -2.0f);

	unsigned int pointLightCount = 0;

	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f, 0.1f, 0.1f, -4.0f, 2.0f, 0.0f, 0.3f, 0.2f, 0.1f);
	//pointLightCount++;
	
	unsigned int spotLightCount = 0;

	spotLights[0] = SpotLight(0.0f, 0.0f, 1.0f, 0.0f, 2.0f,
		-4.0f, 2.0f, 0.0f,
		0.0f, -1.0f, 0.0f, 
		1.0f, 0.0f, 0.0f, 20.0f);
	spotLightCount++;

	shinyMaterial = Material(1.0f, 32);

	GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	glm::mat4 projectionMatrix = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

	// Main Loop
	while (!mainWindow.getShouldClose()) {
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		lastTime = now;

		// Handle user inputs
		glfwPollEvents();

		mainCamera.keyControl(mainWindow.getKeys(), deltaTime);
		mainCamera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear Window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderList[0]->UseShader();
		uniformModel = shaderList[0]->GetModelLocation();
		uniformProjection = shaderList[0]->GetProjectionLocation();
		uniformView = shaderList[0]->GetViewLocation();
		uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
		uniformShininess = shaderList[0]->GetShininessLocation();
		uniformEyePosition = shaderList[0]->GetEyePositionLocation();

		glm::vec3 lowLight = mainCamera.GetCameraPosition();
		lowLight.y -= 0.3f;
		spotLights[0].SetFlash(lowLight, mainCamera.GetCameraDirection());

		shaderList[0]->SetDirectionalLight(&mainLight);
		shaderList[0]->SetPointLight(pointLights, pointLightCount);
		shaderList[0]->SetSpotLight(spotLights, spotLightCount);
		
		//glUniform1f(uniformModel, triOffset);
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(mainCamera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, mainCamera.GetCameraPosition().x, mainCamera.GetCameraPosition().y, mainCamera.GetCameraPosition().z);

		glm::mat4 model(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
		model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		brickTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[0]->RenderMesh();

		model = glm::mat4(1.0f);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//model = glm::rotate(model, 0.0f * toRadians, glm::vec3(1.0f, 1.0f, 1.0f));
		dirtTexture.UseTexture();
		shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
		
		// mainLight.useLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection);

		meshList[1]->RenderMesh();

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}