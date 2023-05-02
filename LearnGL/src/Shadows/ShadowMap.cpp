#include "ShadowMap.h"


namespace YSAoo {
	ShadowMap::ShadowMap()
	{
		FBO = 0;
		ShadowMapUint = 0;
		ShadowWidth = 0;
		ShadowHeight = 0;
	}

	bool ShadowMap::Init(unsigned int Width, unsigned int Height)
	{
		ShadowWidth = Width; ShadowHeight = Height;

		glGenFramebuffers(1, &FBO);

		glGenTextures(1, &ShadowMapUint);
		glBindTexture(GL_TEXTURE_2D, ShadowMapUint);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Width, Height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);

		// GL_REPEAT CHANGE
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		GLfloat BColor[] = { 1.0f, 1.0f, 1.0f, 1.0f };

		glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, BColor);

		glBindFramebuffer(GL_FRAMEBUFFER, FBO);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowMapUint, 0);

		glDrawBuffer(GL_NONE);
		glReadBuffer(GL_NONE);

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			printf("Framebuffer Error: %i\n", Status);
			return false;
		}

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		return true;
	}

	void ShadowMap::Write()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
	}

	void ShadowMap::Read(GLenum TextureUnit)
	{
		glActiveTexture(TextureUnit);
		glBindTexture(GL_TEXTURE_2D, ShadowMapUint);
	}

	ShadowMap::~ShadowMap()
	{
		if (FBO) {
			glDeleteFramebuffers(1, &FBO);
		}

		if (ShadowMapUint) {
			glDeleteTextures(1, &ShadowMapUint);
		}
	}
}