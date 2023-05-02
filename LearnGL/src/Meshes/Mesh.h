#ifndef MESH_H
#define MESH_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <string>

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Objects/GameObject.h"
#include "MaterialProperties/Texture.h"
#include "MaterialProperties/Material.h"

namespace YSAoo {
	class Mesh : public GameObject
	{
	public:
		Mesh();

		void InitMesh(GLfloat* Vertices, unsigned int* Indices, unsigned int NoOfVertices, unsigned int NoOfIndices);
		void BaseRenderMesh();
		void RenderMesh();
		void ClearMesh();
		void AddMatTex(Material* Mat = nullptr, Texture* Tex = nullptr);
		void SetSpecs(GLuint SpecularIntensityLocation = 0, GLuint ShininessLocation = 0);
		void AddSpecs();

		~Mesh();
	protected:
	
	private:
		GLfloat* Vertices;
		unsigned int* Indices;

		GLuint VAO, IBO, VBO;

		unsigned int NoOfVertices, NoOfIndices;

		Material* MeshMaterial;
		Texture* MeshTexture;
		GLuint SpecularIntensityLocation;
		GLuint ShininessLocation;
	};
}

#endif