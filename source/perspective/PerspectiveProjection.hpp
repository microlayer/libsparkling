#ifndef __SPARK_PERSPECTIVE_PERSPECTIVE_HPP_INCLUDED__
#define __SPARK_PERSPECTIVE_PERSPECTIVE_HPP_INCLUDED__

#include "spark/SparkTypes.hpp"

namespace spark {
    namespace perspective {

        /**
        *
        */
        struct PerspectiveProjection
        {
            real32 m_fovy;
            real32 m_aspect;
            real32 m_zNear;
            real32 m_zFar;
        };
    } // end namespace perspective
} // end namespace spark
#endif