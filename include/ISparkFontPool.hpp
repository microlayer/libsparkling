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
        /**
        * @brief Returns a pointer to a Font.
        * FontPool owns all fonts; caller must NOT release/delete.
        */
        virtual spark::font::ISparkFont* getFont(spark::font::E_SYSTEM_FONT_TYPE fontType) = 0;
    };
}
#endif