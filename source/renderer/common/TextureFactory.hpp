#ifndef __SPARK_RENDERER_TEXTUREFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_TEXTUREFACTORY_HPP_INCLUDED__

#include "ISparkTextureFactory.hpp"
#include "ISparkLogger.hpp"
#include <vector>
#include <string>
#include <map>

namespace spark {
    namespace renderer {
        namespace ogl {
            class OGLTexture;
        }
    }
}

namespace spark {
    namespace renderer {
        /**
        *
        */
        class TextureFactory : public spark::renderer::ISparkTextureFactory
        {
        public:
            TextureFactory(spark::log::ISparkLogger* logger);
            ~TextureFactory();

        public: // ISparkTextureFactory
            spark::renderer::ISparkTexture* createOrUpdate(std::string id, uc8_t* data, int32_t width, int32_t height, spark::drawing::E_PIXEL_FORMAT pixelFormat);

        private:
            std::map<std::string, spark::renderer::ogl::OGLTexture*> m_textureMap;
            spark::log::ISparkLogger* m_logger;
        };
    } // end namespace renderer
} // end namespace spark
#endif

