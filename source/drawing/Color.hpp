#ifndef __SPARK_DRAWING_COLOR_HPP_INCLUDED__
#define __SPARK_DRAWING_COLOR_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"

namespace spark::drawing {
    /**
    *
    */
    struct Color
    {
        /**
        *
        */
        Color(void)
        {
        }

        /**
        *
        */
        Color(uc8_t red, uc8_t green, uc8_t blue, uc8_t alpha)
        {
            //Color representation by 4 byte types
            m_red = red;
            m_green = green;
            m_blue = blue;
            m_alpha = alpha;

            // Color representation by 4 real32 types in the range from 0..1 
            m_redf = 1.0f / 255.0f * red;
            m_greenf = 1.0f / 255.0f * green;
            m_bluef = 1.0f / 255.0f * blue;
            m_alphaf = 1.0f / 255.0f * alpha;

            // Color representation by one 32 Bit usigned int type 
            m_r8g8b8a8 = (((red & 0xff) << 24) | ((green & 0xff) << 16) | ((blue & 0xff) << 8) | (alpha & 0xff));
        }

    public:
        // Do not change this order - This guarantees the correct memory layout 
        uc8_t m_red;
        uc8_t m_green;
        uc8_t m_blue;
        uc8_t m_alpha;

        real32 m_redf;
        real32 m_greenf;
        real32 m_bluef;
        real32 m_alphaf;

        uint32_t m_r8g8b8a8;
    };
}
#endif