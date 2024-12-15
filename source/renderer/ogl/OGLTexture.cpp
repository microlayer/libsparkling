#include "OGLTexture.hpp"

namespace spark {
    namespace renderer {
        namespace ogl {
            /**
            *
            */
            OGLTexture::OGLTexture(spark::log::ISparkLogger* logger) : m_logger(logger)
            {

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
                return 0;
            }

            /**
            *
            */
            uint32_t OGLTexture::getWidth() const
            {
                return 0;
            }

            /**
            *
            */
            uint32_t OGLTexture::getHeight() const
            {
                return 0;
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
                glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, 0, 0, 0, GL_LUMINANCE, GL_UNSIGNED_BYTE, 0);

                GLenum err = glGetError();
                if (glGetError() != err)
                {
                    m_logger->error("Error loading texture into OpenGL with reason: %s code: %i", "Undefined", err);
                }

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

                glBindTexture(GL_TEXTURE_2D, 0);
            }

            /**
            *
            */
            uint32_t OGLTexture::getHandle() const
            {
                return 0;
            }
        } // end namespace ogl
    } // end namespace renderer
} // end namespace spark
