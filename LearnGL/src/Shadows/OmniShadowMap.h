#ifndef OMNISHADOWMAP_H
#define OMNISHADOWMAP_H
#include "Shadows/ShadowMap.h"

namespace YSAoo {
    class OmniShadowMap :
        public ShadowMap
    {
    public:
        OmniShadowMap();

        virtual bool Init(unsigned int Width, unsigned int Height);

        virtual void Write();

        virtual void Read(GLenum TextureUnit);

        ~OmniShadowMap();
    };
}
#endif