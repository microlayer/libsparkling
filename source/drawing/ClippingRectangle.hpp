#ifndef __SPARK_DRAWING_CLIPPINGRECTANGLE_HPP_INCLUDED__
#define __SPARK_DRAWING_CLIPPINGRECTANGLE_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"

namespace spark {
    namespace drawing {

        /**
        *
        */
        struct ClippingRectangle
        {
            /**
            *
            */
            ClippingRectangle(void)
            {

            }

            /**
            *
            */
            ClippingRectangle(uint16_t x, uint16_t y, uint16_t width, uint16_t height) : m_x(x), m_y(y), m_width(width), m_height(height)
            {
            }

        public:
            uint16_t m_x;
            uint16_t m_y;
            uint16_t m_width;
            uint16_t m_height;
        };
    } // end namespace drawing
} // end namespace spark
#endif