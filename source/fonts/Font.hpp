#ifndef __SPARK_FONT_FONT_HPP
#define __SPARK_FONT_FONT_HPP

#include "ISparkFont.hpp"
#include "embedded/Arial16.hpp"

namespace spark {
    namespace font {
        /**
        *
        */
        class Font : public ISparkFont
        {
        public:
            Font();
            ~Font();
        public:
            spark::font::BitmapFontInfo getBitmapFontInfo(uint16_t size) const;
            uc8_t* getFontMap() const;
        };
    } // end namespace font
} // end namespace spark
#endif