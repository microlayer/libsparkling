#ifndef __SPARK_RENDERER_OGL_OGLTEXTURE_HPP_INCLUDED__
#define __SPARK_RENDERER_OGL_OGLTEXTURE_HPP_INCLUDED__

#include <GL/glew.h>
#include "ISparkTexture.hpp"
#include "ISparkLogger.hpp"

namespace spark {
    namespace renderer {
        namespace ogl {
            /**
            *
            */
            class OGLTexture : public ISparkTexture
            {
            public:
                OGLTexture(spark::log::ISparkLogger* logger, uc8_t* data, int32_t width, int32_t height);
                ~OGLTexture();

            public: // ISparkTexture
                uc8_t* getImageAsStream() const;
                uint32_t getWidth() const;
                uint32_t getHeight() const;
                spark::drawing::E_PIXEL_FORMAT getPixelFormat() const;
                bool hasMipMaps() const;
                void bind();
                uint32_t getHandle() const;

            private:
                spark::log::ISparkLogger* m_logger;
                GLuint m_textureId;
                uc8_t* m_data;
                uint32_t m_width;
                uint32_t m_height;
            };
        } // end namespace ogl
    } // end namespace renderer
} // end namespace spark
#endif
