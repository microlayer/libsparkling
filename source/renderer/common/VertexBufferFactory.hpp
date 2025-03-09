#ifndef __SPARK_RENDERER_VERTEXBUFFERFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_VERTEXBUFFERFACTORY_HPP_INCLUDED__

#include "ISparkVertexBufferFactory.hpp"
#include "ISparkVertexBuffer.hpp"
#include "ISparkLogger.hpp"
#include <string>

namespace spark {
    namespace renderer {
        /**
        *
        */
        class VertexBufferFactory : public spark::renderer::ISparkVertexBufferFactory
        {
        public:
            VertexBufferFactory(spark::log::ISparkLogger* logger);
            ~VertexBufferFactory();

        public:
            spark::renderer::ISparkVertexBuffer* createOrUpdate(std::string id);
        };
    } // end namespace renderer
} // end namespace spark
#endif