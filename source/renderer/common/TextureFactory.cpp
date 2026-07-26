#include "TextureFactory.hpp"
#include "renderer/texture/OGLTexture.hpp"

namespace spark::renderer {
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
        for (auto& entry : m_textureMap)
        {
            entry.second->release();
        }

        m_textureMap.clear();
    }

    /**
    *
    */
    spark::renderer::ISparkTexture* TextureFactory::getOrCreateTexture(std::string id, uc8_t* data, int32_t width, int32_t height, spark::drawing::E_PIXEL_FORMAT pixelFormat)
    {
        if (m_textureMap.find(id) == m_textureMap.end())
        {
            spark::renderer::texture::OGLTexture* texture = new spark::renderer::texture::OGLTexture(data, width, height, pixelFormat, m_logger);
            m_textureMap[id] = texture;
            texture->addRef();
            return texture;
        }
        else
        {
            spark::renderer::texture::OGLTexture* texture = m_textureMap[id];
            texture->addRef();
            return texture;
        }
    }

    /**
    *
    */
    spark::renderer::ISparkTexture* TextureFactory::createDepthTexture(int32_t width, int32_t height)
    {
        spark::renderer::texture::OGLTexture* texture = new spark::renderer::texture::OGLTexture(width, height, m_logger);
        return texture;
    }
}
