#include "TextureFactory.hpp"
#include "renderer/texture/OGLTexture.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        TextureFactory::TextureFactory(spark::log::ISparkLogger* logger) : m_logger(logger)
        {

        }

        /**
        *
        */
        TextureFactory::~TextureFactory()
        {

        }

        /**
        *
        */
        spark::renderer::ISparkTexture* TextureFactory::createOrUpdate(std::string id, uc8_t* data, int32_t width, int32_t height, spark::drawing::E_PIXEL_FORMAT pixelFormat)
        {
            if (m_textureMap.find(id) == m_textureMap.end())
            {
                spark::renderer::texture::OGLTexture* texture = new spark::renderer::texture::OGLTexture(m_logger, data, width, height, pixelFormat);
                m_textureMap[id] = texture;
                return texture;
            }
            else
            {
                return m_textureMap[id];
            }
        }
    }
}
