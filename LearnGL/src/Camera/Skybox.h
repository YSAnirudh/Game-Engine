#ifndef SKYBOX_H
#define SKYBOX_H

#include <vector>
#include <string>

#include <GL/glew.h>

#include "Common.h"
#include "Shaders/Shader.h"

#include "Meshes/Mesh.h"
#include "Shaders/Shader.h"

namespace YSAoo {
	class Skybox
	{
	public:
		Skybox();
		Skybox(std::vector<std::string> FaceLocations);

		void DrawSkyBox(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix);

		~Skybox();

	private:
		Mesh* SkyMesh;
		Shader* SkyShader;

		GLuint TextureID;
		GLuint UniformProjection;
		GLuint UniformView;
	};
}
#endif