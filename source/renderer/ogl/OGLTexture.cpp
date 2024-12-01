#include "OGLTexture.hpp"

namespace spark {
    namespace renderer {
        namespace ogl {
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
            void OGLTexture::setActive()
            {

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
