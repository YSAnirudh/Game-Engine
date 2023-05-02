#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Common.h"
namespace YSAoo {
	Texture::Texture()
	{
		Width = 0;
		Height = 0;
		TextureID = 0;
		BitDepth = 0;
		TextureLocation = "";
	}

	Texture::Texture(const char* FileLoc)
	{
		Width = 0;
		Height = 0;
		TextureID = 0;
		BitDepth = 0;
		TextureLocation = FileLoc;
	}

	bool Texture::LoadTextureA()
	{
		unsigned char* TexData = stbi_load(TextureLocation, &Width, &Height, &BitDepth, 4);
		if (!TexData) {
			printf("Failed to file File Location: %s\n", TextureLocation);
			return false;
		}

		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, TexData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(TexData);
		return true;
	}

	bool Texture::LoadTexture()
	{
		unsigned char* TexData = stbi_load(TextureLocation, &Width, &Height, &BitDepth, 0);

		if (!TexData) {
			printf("Failed to file File Location: %s\n", TextureLocation);
			return false;
		}
		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, TexData);
		glGenerateMipmap(GL_TEXTURE_2D);

		glBindTexture(GL_TEXTURE_2D, 0);
		stbi_image_free(TexData);
		return true;
	}

	void Texture::UseTexture()
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureID);
	}

	void Texture::ClearTexture()
	{
		glDeleteTextures(1, &TextureID);
		TextureID = 0;
		Width = 0;
		Height = 0;
		BitDepth = 0;
		TextureLocation = "";
	}

	Texture::~Texture()
	{
		ClearTexture();
	}
}