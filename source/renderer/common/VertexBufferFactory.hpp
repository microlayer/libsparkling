#ifndef __SPARK_RENDERER_VERTEXBUFFERFACTORY_HPP_INCLUDED__
#define __SPARK_RENDERER_VERTEXBUFFERFACTORY_HPP_INCLUDED__

#include "ISparkVertexBufferFactory.hpp"
#include "ISparkVertexBuffer.hpp"
#include "ISparkMesh.hpp"
#include "ISparkLogger.hpp"
#include <string>
#include <map>

namespace spark {
    namespace renderer {
        namespace vertexbuffer {
            class OGLVertexBuffer;
        }
    }
}

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
            spark::renderer::ISparkVertexBuffer* createOrUpdate(std::string id, std::vector<spark::drawing::Vertex3>& vertices);
            spark::renderer::ISparkVertexBuffer* createOrUpdate(std::string id, spark::mesh::ISparkMesh* mesh);

        private:
            std::map<std::string, spark::renderer::vertexbuffer::OGLVertexBuffer*> m_vertexBufferMap;
            spark::log::ISparkLogger* m_logger;
        };
    } // end namespace renderer
} // end namespace spark
#endif