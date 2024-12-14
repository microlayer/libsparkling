#ifndef __SPARK_RENDERER_TEXTUREFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_TEXTUREFACTORY_HPP_INCLUDED__

#include "ISparkTextureFactory.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        class TextureFactory : public spark::renderer::ISparkTextureFactory
        {
        public:
            TextureFactory();
            ~TextureFactory();

        public: // ISparkTextureFactory
            spark::renderer::ISparkTexture* CreateOrUpdate(uc8_t* data);
        };
    }
}
#endif

