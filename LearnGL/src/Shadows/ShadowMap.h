#ifndef SHADOWMAP_H
#define SHADOWMAP_H

#include <stdio.h>

#include <GL/glew.h>

namespace YSAoo {
	class ShadowMap
	{
	public:
		ShadowMap();

		virtual bool Init(unsigned int Width, unsigned int Height);

		virtual void Write();

		virtual void Read(GLenum TextureUnit);

		inline GLuint GetShadowWidth() { return ShadowWidth; };
		inline GLuint GetShadowHeight() { return ShadowHeight; };

		~ShadowMap();

	protected:
		GLuint FBO, ShadowMapUint;

		unsigned int ShadowWidth, ShadowHeight;
	};
}



#endif