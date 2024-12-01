#ifndef __SPARK_FONT_BITMAPGLYPHINFO_HPP
#define __SPARK_FONT_BITMAPGLYPHINFO_HPP

#include "spark/SparkTypes.hpp"

namespace spark {
    namespace font {
        /**
        *
        */
        struct BitmapGlyphInfo
        {
            c8_t m_charId;
            real32 m_uo;
            real32 m_vo;
            real32 m_normWidth;
            real32 m_normHeight;
            int32_t m_width;
            int32_t m_height;
            int32_t m_xOffset;
            int32_t m_yOffset;
            int32_t m_xAdvance;
        };
    } // end namespace font
} // end namespace spark
#endif