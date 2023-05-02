#ifndef GBUFFERSHADER_H
#define GBUFFERSHADER_H

#include <GL/glew.h>

namespace YSAoo {
	class GBufferShader
	{
	public:

		enum GBUFFER_TEXTURE_TYPE {
			GBUFFER_TEXTURE_TYPE_POSITION,
			GBUFFER_TEXTURE_TYPE_DIFFUSE,
			GBUFFER_TEXTURE_TYPE_NORMAL,
			GBUFFER_TEXTURE_TYPE_TEXCOORD,
			GBUFFER_NUM_TEXTURES
		};

		GBufferShader();

		bool GBufferInit();
		void Write();
		void ReadGBuffer();
		void Read();
		void SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType);

		bool Init();
		void StartFrame();
		void BindForGeomPass();
		void BindForStencilPass();
		void BindForLightPass();
		void BindForFinalPass();

		~GBufferShader();
	private:
		GLuint gBufferFBO;
		GLuint gTextures[GBUFFER_NUM_TEXTURES];
		GLuint gDepth;
		GLuint gFinal;
	};
}

#endif
