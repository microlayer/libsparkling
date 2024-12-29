#ifndef __SPARK_FONT_ISPARKFONT_HPP_INCLUDED__
#define __SPARK_FONT_ISPARKFONT_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "fonts/BitmapFontInfo.hpp"

namespace spark {
    namespace font {
        /**
        *
        */
        enum E_SYSTEM_FONT_TYPE
        {
            ESFT_ARIAL_16 = 1
        };

        /**
        *
        */
        class ISparkFont : public spark::SparkRefCount
        {
        public:
            virtual spark::font::BitmapFontInfo getBitmapFontInfo(uint16_t size) const = 0;
            virtual uc8_t* getFontMap() const = 0;
        };

    } // end namespace font
} // end namespace spark
#endif