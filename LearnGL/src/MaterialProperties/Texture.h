#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>

namespace YSAoo {
	class Texture
	{
	public:
		Texture();
		Texture(const char* FileLoc);

		bool LoadTexture();
		bool LoadTextureA();
		void UseTexture();
		void ClearTexture();

		~Texture();
	private:
		GLuint TextureID;
		int Width, Height, BitDepth;

		const char* TextureLocation;
	};
}
#endif