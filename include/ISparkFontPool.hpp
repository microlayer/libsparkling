#ifndef __SPARK_FONT_ISPARKFONTPOOL_HPP_INCLUDED__
#define __SPARK_FONT_ISPARKFONTPOOL_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkFont.hpp"

namespace spark::font {
    /**
    *
    */
    class ISparkFontPool : public spark::SparkRefCount
    {
    public:
        virtual spark::font::ISparkFont* getFont() = 0;
    };
}
#endif