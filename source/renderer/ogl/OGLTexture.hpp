#ifndef __SPARK_RENDERER_OGL_HPP_INCLUDED__
#define __SPARK_RENDERER_OGL_HPP_INCLUDED__

#include "ISparkTexture.hpp"

namespace spark {
    namespace renderer {
        namespace ogl {
            /**
            *
            */
            class OGLTexture : public ISparkTexture
            {
            public:
                OGLTexture();
                ~OGLTexture();

            public: // ISparkTexture
                uc8_t* getImageAsStream() const;
                uint32_t getWidth() const;
                uint32_t getHeight() const;
                spark::drawing::E_PIXEL_FORMAT getPixelFormat() const;
                bool hasMipMaps() const;
                void setActive();
                uint32_t getHandle() const;
            };
        } // end namespace ogl
    } // end namespace renderer
} // end namespace spark
#endif
