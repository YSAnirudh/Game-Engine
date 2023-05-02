#pragma once

#include <GL/glew.h>
#include "stb_image.h"

class Texture {
public: 
	Texture();
	Texture(const char* fileLocation);

	bool LoadTexture();
	bool LoadTextureAlpha();
	void UseTexture();
	void ClearTexture();

	~Texture();

private:
	GLuint textureID;

	int width, height, bitDepth;

	const char* fileLocation;
};

