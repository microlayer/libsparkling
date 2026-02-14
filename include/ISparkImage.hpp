#ifndef __SPARK_DRAWING_ISPARKIMAGE_HPP_INCLUDED__
#define __SPARK_DRAWING_ISPARKIMAGE_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "drawing/PixelFormat.hpp"
#include "ISparkTexture.hpp"
#include <string>

namespace spark::drawing {
    /**
    *
    */
    class ISparkImage : public virtual spark::SparkRefCount
    {
    public:
        virtual uc8_t* getImageAsStream() const = 0;
        virtual uint32_t getWidth() const = 0;
        virtual uint32_t getHeight() const = 0;
        virtual spark::drawing::E_PIXEL_FORMAT getPixelFormat() const = 0;
        virtual std::string getHash() const = 0;
        virtual void setTexture(spark::renderer::ISparkTexture* texture) = 0;
    };
}
#endif