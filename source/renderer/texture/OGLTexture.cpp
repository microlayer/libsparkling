#include "OGLTexture.hpp"

namespace spark::renderer::texture {
    /**
    *
    */
    OGLTexture::OGLTexture(
        spark::log::ISparkLogger* logger,
        uc8_t* data,
        int32_t width,
        int32_t height,
        spark::drawing::E_PIXEL_FORMAT pixelFormat) :
        m_logger(logger),
        m_data(data),
        m_width(width),
        m_height(height),
        m_pixelFormat(pixelFormat),
        m_textureId(0)
    {
        m_logger->info("Start creating texture");

        glGenTextures(1, &m_textureId);
        glBindTexture(GL_TEXTURE_2D, m_textureId);

        if (spark::drawing::E_RGBA8 == pixelFormat)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
        }
        else if (spark::drawing::E_GRAY8 == pixelFormat)
        {
            // Core Profile compatible replacement for the deprecated internal format GL_LUMINANCE
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, m_data);
        }
        else
        {
            m_logger->error("Unsupported pixel format, creating empty texture");
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R8, m_width, m_height, 0, GL_RED, GL_UNSIGNED_BYTE, NULL);
        }

        GLenum err = glGetError();
        if (err != GL_NO_ERROR)
        {
            m_logger->error("Error loading texture into OpenGL with reason: %s code: %i", "Undefined", err);
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        m_logger->info("Creating texture done");
    }

    /**
    *
    */
    OGLTexture::~OGLTexture()
    {
        if (m_textureId != 0)
        {
            glDeleteTextures(1, &m_textureId);
        }
    }

    /**
    *
    */
    uc8_t* OGLTexture::getImageAsStream() const
    {
        return m_data;
    }

    /**
    *
    */
    uint32_t OGLTexture::getWidth() const
    {
        return m_width;
    }

    /**
    *
    */
    uint32_t OGLTexture::getHeight() const
    {
        return m_height;
    }

    /**
    *
    */
    spark::drawing::E_PIXEL_FORMAT OGLTexture::getPixelFormat() const
    {
        return m_pixelFormat;
    }

    /**
    *
    */
    bool OGLTexture::hasMipMaps() const
    {
        return 0;
    }

    /**
    *
    */
    void OGLTexture::bind()
    {
        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }

    /**
    *
    */
    uint32_t OGLTexture::getHandle() const
    {
        return m_textureId;
    }
} // end namespace spark
