#ifndef __SPARK_RENDERER_ISPARKVERTEXBUFFER_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKVERTEXBUFFER_HPP_INCLUDED__

#include "SparkRefCount.hpp"

namespace spark {
    namespace renderer {
        /**
        *
        */
        class ISparkVertexBuffer : public virtual spark::SparkRefCount
        {
        public:
            virtual void drawPoints() = 0;
            virtual void drawLines() = 0;
            virtual void drawTriangles() = 0;
        };
    } // end namespace renderer
} // end namespace spark
#endif