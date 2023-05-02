#include "OmniShadowMap.h"
namespace YSAoo {
    OmniShadowMap::OmniShadowMap() : ShadowMap()
    {
    }
    bool OmniShadowMap::Init(unsigned int Width, unsigned int Height)
    {
        ShadowHeight = Height; ShadowWidth = Width;

        glGenFramebuffers(1, &FBO);

        glGenTextures(1, &ShadowMapUint);
        glBindTexture(GL_TEXTURE_CUBE_MAP, ShadowMapUint);

        for (size_t i = 0; i < 6; i++) {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, ShadowWidth, ShadowHeight, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindFramebuffer(GL_FRAMEBUFFER, FBO);
        glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, ShadowMapUint, 0);

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

    void OmniShadowMap::Write()
    {
        glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FBO);
    }

    void OmniShadowMap::Read(GLenum TextureUnit)
    {
        glActiveTexture(TextureUnit);
        glBindTexture(GL_TEXTURE_CUBE_MAP, ShadowMapUint);
    }

    OmniShadowMap::~OmniShadowMap()
    {
        if (FBO) {
            glDeleteFramebuffers(1, &FBO);
        }

        if (ShadowMapUint) {
            glDeleteTextures(1, &ShadowMapUint);
        }
    }
}