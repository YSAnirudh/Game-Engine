#include "Mesh.h"

YSAoo::Mesh::Mesh()
{
	VAO = 0;
	IBO = 0;
	VBO = 0;
	NoOfIndices = 0;
	NoOfVertices = 0;
	Vertices = nullptr;
	Indices = nullptr;
}

void YSAoo::Mesh::InitMesh(GLfloat* Vertices, unsigned int* Indices, unsigned int NoOfVertices, unsigned int NoOfIndices)
{
	this->NoOfVertices = NoOfVertices;
	this->NoOfIndices = NoOfIndices;

	this->Indices = Indices;
	
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * NoOfIndices, Indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * NoOfVertices, Vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]) * 8, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]) * 8, (void*)(sizeof(Vertices[0]) * 3));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices[0]) * 8, (void*)(sizeof(Vertices[0]) * 5));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	//printf("%d, %d, %d\n", VAO, VBO, IBO);
}

void YSAoo::Mesh::BaseRenderMesh() {
	if (MeshMaterial) {
		MeshMaterial->UseMaterial(SpecularIntensityLocation, ShininessLocation);
	}

	if (MeshTexture) {
		MeshTexture->UseTexture();
	}
	else {
		MeshTexture = new Texture("Textures/plain.png");
		MeshTexture->LoadTextureA();
		MeshTexture->UseTexture();
	}
	RenderMesh();
}

void YSAoo::Mesh::RenderMesh()
{
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glDrawElements(GL_TRIANGLES, NoOfIndices, GL_UNSIGNED_INT, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void YSAoo::Mesh::AddMatTex(Material* Mat, Texture* Tex)
{
	MeshMaterial = Mat;
	MeshTexture = Tex;
}

void YSAoo::Mesh::ClearMesh()
{
	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (IBO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}
	NoOfIndices = 0;
	NoOfVertices = 0;
}

void YSAoo::Mesh::SetSpecs(GLuint SpecularIntensityLocation, GLuint ShininessLocation)
{
	this->SpecularIntensityLocation = SpecularIntensityLocation;
	this->ShininessLocation = ShininessLocation;
}

void YSAoo::Mesh::AddSpecs()
{
	if (MeshMaterial) {
		MeshMaterial->UseMaterial(SpecularIntensityLocation, ShininessLocation);
	}
}

YSAoo::Mesh::~Mesh()
{
	MeshTexture->ClearTexture();
	delete MeshTexture;
	MeshTexture = nullptr;
	delete MeshMaterial;
	MeshMaterial = nullptr;
	ClearMesh();
}
