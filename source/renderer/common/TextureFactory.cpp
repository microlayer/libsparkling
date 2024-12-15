#include "TextureFactory.hpp"
#include "renderer/ogl/OGLTexture.hpp"

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
            for (auto pair : m_textureMap)
            {
                delete pair.second;
            }
        }

        /**
        *
        */
        spark::renderer::ISparkTexture* TextureFactory::createOrUpdate(std::string id, uc8_t* data, int32_t width, int32_t height)
        {
            if (m_textureMap.find(id) == m_textureMap.end())
            {
                spark::renderer::ogl::OGLTexture* texture = new spark::renderer::ogl::OGLTexture(m_logger);
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
