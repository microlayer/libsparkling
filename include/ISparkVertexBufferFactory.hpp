#ifndef __SPARK_RENDERER_ISPARKVERTEXBUFFERFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_ISPARKVERTEXBUFFERFACTORY_HPP_INCLUDED__

#include "SparkRefCount.hpp"
#include "ISparkVertexBuffer.hpp"
#include <string>

namespace spark {
    namespace renderer {
        /**
        *
        */
        class ISparkVertexBufferFactory : public virtual spark::SparkRefCount
        {
        public:
            virtual spark::renderer::ISparkVertexBuffer* createOrUpdate(std::string id) = 0;
        };
    } // end namespace renderer
} // end namespace spark
#endif