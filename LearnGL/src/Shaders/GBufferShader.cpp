#include "GBufferShader.h"
#include "Common.h"
namespace YSAoo {
	GBufferShader::GBufferShader()
	{
		gBufferFBO = 0;
		gDepth = 0;
		gFinal = 0;
		gTextures[0] = 0;
	}
	bool GBufferShader::Init()
	{
		glGenFramebuffers(1, &gBufferFBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBufferFBO);

		glGenTextures(ARRAY_SIZE_IN_ELEM(gTextures), gTextures);
		glGenTextures(1, &gDepth);
		glGenTextures(1, &gFinal);

		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEM(gTextures); i++) {
			glBindTexture(GL_TEXTURE_2D, gTextures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, gTextures[i], 0);
		}

		glBindTexture(GL_TEXTURE_2D, gDepth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH32F_STENCIL8, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_DEPTH_STENCIL, GL_FLOAT_32_UNSIGNED_INT_24_8_REV, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, gDepth, 0);

		glBindTexture(GL_TEXTURE_2D, gFinal);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT4, GL_TEXTURE_2D, gFinal, 0);

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			printf("Framebuffer Error: %i\n", Status);
			return false;
		}

		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		return true;
	}
	bool GBufferShader::GBufferInit()
	{
		// Create the FBO
		glGenFramebuffers(1, &gBufferFBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBufferFBO);

		// Create the gbuffer textures
		glGenTextures(ARRAY_SIZE_IN_ELEM(gTextures), gTextures);
		glGenTextures(1, &gDepth);

		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEM(gTextures); i++) {
			glBindTexture(GL_TEXTURE_2D, gTextures[i]);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, gTextures[i], 0);
		}

		// depth
		glBindTexture(GL_TEXTURE_2D, gDepth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, WINDOW_WIDTH, WINDOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT,
			NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, gDepth, 0);

		GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
		glDrawBuffers(ARRAY_SIZE_IN_ELEM(DrawBuffers), DrawBuffers);

		GLenum Status = glCheckFramebufferStatus(GL_FRAMEBUFFER);

		if (Status != GL_FRAMEBUFFER_COMPLETE) {
			printf("FB error, status: 0x%x\n", Status);
			return false;
		}

		// restore default FBO
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		return true;
	}
	void GBufferShader::Write()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBufferFBO);
	}

	void GBufferShader::ReadGBuffer()
	{
		glBindFramebuffer(GL_READ_FRAMEBUFFER, gBufferFBO);
	}

	void GBufferShader::Read()
	{
		//glBindFramebuffer(GL_READ_FRAMEBUFFER, gBufferFBO);
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEM(gTextures); i++) {
			glActiveTexture(GL_TEXTURE3 + i);
			glBindTexture(GL_TEXTURE_2D, gTextures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
		}
	}

	void GBufferShader::SetReadBuffer(GBUFFER_TEXTURE_TYPE TextureType)
	{
		glReadBuffer(GL_COLOR_ATTACHMENT0 + TextureType);
	}

	void GBufferShader::StartFrame()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBufferFBO);
		glDrawBuffer(GL_COLOR_ATTACHMENT4);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void GBufferShader::BindForGeomPass()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, gBufferFBO);
		GLenum ColorAttachments[] = {
			GL_COLOR_ATTACHMENT0,
			GL_COLOR_ATTACHMENT1,
			GL_COLOR_ATTACHMENT2
		};
		glDrawBuffers(ARRAY_SIZE_IN_ELEM(ColorAttachments), ColorAttachments);
	}

	void GBufferShader::BindForStencilPass()
	{
		glDrawBuffer(GL_NONE);
	}

	void GBufferShader::BindForLightPass()
	{
		glDrawBuffer(GL_COLOR_ATTACHMENT4);
		for (unsigned int i = 0; i < ARRAY_SIZE_IN_ELEM(gTextures); i++) {
			glActiveTexture(GL_TEXTURE3 + i);
			glBindTexture(GL_TEXTURE_2D, gTextures[GBUFFER_TEXTURE_TYPE_POSITION + i]);
		}
	}

	void GBufferShader::BindForFinalPass()
	{
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glBindFramebuffer(GL_READ_FRAMEBUFFER, gBufferFBO);
		glReadBuffer(GL_COLOR_ATTACHMENT4);
	}

	GBufferShader::~GBufferShader()
	{
	}
}