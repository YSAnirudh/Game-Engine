#include "Skybox.h"

YSAoo::Skybox::Skybox()
{
}

YSAoo::Skybox::Skybox(std::vector<std::string> FaceLocations)
{
	SkyShader = new Shader();
	SkyShader->CreateFromFiles("Shaders/skybox.vert", "Shaders/skybox.frag");

	UniformProjection = SkyShader->GetProjectionMatrixLocation();
	UniformView = SkyShader->GetViewMatrixLocation();

	// Texture
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);

	int Width, Height, BitDepth;

	for (size_t i = 0; i < 6; i++) {
		int TexNumber = 0;
		if (FaceLocations[i].find(".png") != std::string::npos) {
			TexNumber = 4;
		}
		unsigned char* TexData = stbi_load(FaceLocations[i].c_str(), &Width, &Height, &BitDepth, TexNumber);
		if (!TexData) {
			printf("Failed to file File Location: %s\n", FaceLocations[i].c_str());
			return;
		}

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, TexData);
		stbi_image_free(TexData);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Mesh setup
	unsigned int SkyboxIndices[] = {
		0,1,2,
		2,1,3,
		2,3,5,
		5,3,7,
		5,7,4,
		4,7,6,
		4,6,0,
		0,6,1,
		4,0,5,
		5,0,2,
		1,6,3,
		3,6,7
	};

	float SkybozVertices[] = {
		-1.0f, 1.0f, -1.0f,  0.0f,0.0f,0.0f,0.0f,0.0f,
		-1.0f, -1.0f, -1.0f,  0.0f,0.0f,0.0f,0.0f,0.0f,
		1.0f, 1.0f, -1.0f,  0.0f,0.0f,0.0f,0.0f,0.0f,
		1.0f, -1.0f, -1.0f,  0.0f,0.0f,0.0f,0.0f,0.0f,
		-1.0f, 1.0f, 1.0f,  0.0f,0.0f,0.0f,0.0f,0.0f,
		1.0f, 1.0f, 1.0f,  0.0f,0.0f,0.0f,0.0f,0.0f,
		-1.0f, -1.0f, 1.0f,  0.0f,0.0f,0.0f,0.0f,0.0f,
		1.0f, -1.0f, 1.0f,  0.0f,0.0f,0.0f,0.0f,0.0f,
	};

	SkyMesh = new Mesh();
	SkyMesh->InitMesh(SkybozVertices, SkyboxIndices, 64, 36);
}

void YSAoo::Skybox::DrawSkyBox(glm::mat4 ViewMatrix, glm::mat4 ProjectionMatrix)
{
	ViewMatrix = glm::mat4(glm::mat3(ViewMatrix));

	glDepthMask(GL_FALSE);

	SkyShader->UseShader();

	glUniformMatrix4fv(UniformProjection, 1, GL_FALSE, glm::value_ptr(ProjectionMatrix));
	glUniformMatrix4fv(UniformView, 1, GL_FALSE, glm::value_ptr(ViewMatrix));

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, TextureID);

	SkyShader->Validate();

	SkyMesh->RenderMesh();

	glDepthMask(GL_TRUE);
}

YSAoo::Skybox::~Skybox()
{
	if (SkyMesh) {
		delete SkyMesh;
		SkyMesh = nullptr;
	}

	if (SkyShader) {
		delete SkyShader;
		SkyShader = nullptr;
	}
}
