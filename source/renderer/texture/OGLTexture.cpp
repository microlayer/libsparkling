#include "OGLTexture.hpp"

namespace spark {
    namespace renderer {
        namespace ogl {
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
                m_textureId(0)
            {
                m_logger->info("Start creating texture");

                glGenTextures(1, &m_textureId);
                glBindTexture(GL_TEXTURE_2D, m_textureId);

                if (!glIsTexture(m_textureId))
                {
                    m_logger->error("Invalid texture ID!");
                }

                if (spark::drawing::E_RGBA8 == pixelFormat)
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_data);
                }
                if (spark::drawing::E_GRAY8 == pixelFormat)
                {
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, m_width, m_height, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, m_data);
                }

                GLenum err = glGetError();
                if (glGetError() != err)
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
                return spark::drawing::E_PIXEL_FORMAT::E_GRAY8;
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
        } // end namespace ogl
    } // end namespace renderer
} // end namespace spark
