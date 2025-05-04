#ifndef __SPARK_PERSPECTIVE_VIEWPORT_HPP_INCLUDED__
#define __SPARK_PERSPECTIVE_VIEWPORT_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"

namespace spark {
    namespace perspective {

        /**
        *
        */
        struct Viewport
        {
        public:
            /**
            *
            */
            Viewport()
            {
            }

            /**
            *
            */
            Viewport(uint16_t x, uint16_t y, uint16_t width, uint16_t height) : m_x(x), m_y(y), m_width(width), m_height(height)
            {
            }

            int16_t m_x;
            int16_t m_y;
            int16_t m_width;
            int16_t m_height;
        };
    } // end namespace perspective
} // end namespace spark
#endif