#ifndef __SPARK_RENDERER_ISPARKTEXTURE_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKTEXTURE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "drawing/PixelFormat.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        class ISparkTexture : public virtual spark::SparkRefCount
        {
        public:
            virtual uc8_t* getImageAsStream() const = 0;
            virtual uint32_t getWidth() const = 0;
            virtual uint32_t getHeight() const = 0;
            virtual spark::drawing::E_PIXEL_FORMAT getPixelFormat() const = 0;
            virtual bool hasMipMaps() const = 0;
            virtual void setActive() = 0;
            virtual uint32_t getHandle() const = 0;
        };
    } // end namespace renderer
} // end namespace spark
#endif