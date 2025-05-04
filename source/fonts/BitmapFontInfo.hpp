#ifndef __SPARK_FONT_BITMAPFONTINFO_HPP
#define __SPARK_FONT_BITMAPFONTINFO_HPP

#include "spark/SparkTypes.hpp"
#include "BitmapGlyphInfo.hpp"

namespace spark {
    namespace font {

        /**
        *
        */
        struct BitmapFontInfo
        {
            uint32_t m_textureWidth;
            uint32_t m_textureHeight;
            BitmapGlyphInfo m_bitmapGlyphs[256];
        };
    } // end namespace font
} // end namespace spark
#endif